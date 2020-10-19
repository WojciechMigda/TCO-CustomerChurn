#include "model_params.hpp"
#include "infer.hpp"
#include "train.hpp"

#include "spdlog/spdlog.h"
#include "clipp.hpp"

#include <iostream>
#include <fstream>


struct is_natural
{
    bool operator()(std::string const & arg) const
    {
        unsigned int val = 0;

        try
        {
            val = std::stoi(arg);
        }
        catch (std::invalid_argument const & e)
        {
            return false;
        }

        return val > 0;
    }
};


struct is_nonnegative
{
    bool operator()(std::string const & arg) const
    {
        unsigned int val = 0;

        try
        {
            val = std::stoi(arg);
        }
        catch (std::invalid_argument const & e)
        {
            return false;
        }

        return val >= 0;
    }
};


bool bad_filename(std::string const & fname)
{
    std::ifstream f(fname);

    bool ok = f.is_open();

    if (not ok)
    {
        spdlog::error("Cannot open file {}", fname);
    }

    return not ok;
}


int main(int argc, char **argv)
{
    unsigned int ts_threshold = 8000;
    float ts_s = 4.0;
    unsigned int ts_clauses = 3200;
    int ts_njobs = 2;
    int ts_max_weight = std::numeric_limits<int>::max();
    bool boost_tpf = true;
    unsigned int nepochs = 20u;
    std::string model_ifname;
    std::string csv_ifname;
    std::string encoder_ifname;
    bool do_infer = false;


    auto inference = (
        clipp::command("infer").set(do_infer, true).doc("Request inference using existing model"),
        clipp::required("--datafile", "-d").doc("Input CSV file for training or inference") & clipp::value("CSV data file to read from", csv_ifname),
        clipp::required("--encoding", "-e").doc("Input JSON file with input encoding parameters") & clipp::value("JSON encoding file to read from", encoder_ifname),
        clipp::required("--model", "-m").doc("Pre-trained input model to load") & clipp::value("JSON-ized model file to read from", model_ifname)
    );

    auto training = (
        clipp::command("train").set(do_infer, false).doc("Request model training / augmenting"),
        clipp::required("--datafile", "-d").doc("Input CSV file for training or inference") & clipp::value("CSV data file to read from", csv_ifname),
        clipp::required("--encoding", "-e").doc("Input JSON file with input encoding parameters") & clipp::value("JSON encoding file to read from", encoder_ifname),
        clipp::option("--model", "-m").doc("Pre-trained input model to load") & clipp::value("JSON-ized model file to read from", model_ifname),

        clipp::option("--tsetlini-threshold", "-T").doc("Threshold parameter for the Tsetlini model") & clipp::value(is_natural(), "threshold=" + std::to_string(ts_threshold), ts_threshold),
        clipp::option("--tsetlini-s", "-s").doc("Specificity parameter for the Tsetlini model") & clipp::value("s=" + std::to_string(ts_s), ts_s),
        clipp::option("--tsetlini-clauses", "-C").doc("Number of clauses parameter for the Tsetlini model") & clipp::value(is_natural(), "clauses=" + std::to_string(ts_clauses), ts_clauses),
        (
            clipp::option("--tsetlini-boost-tpf", "-B").set(boost_tpf, true) |
            clipp::option("--tsetlini-no-boost-tpf", "-b").set(boost_tpf, false)
        ).doc("Boost (T)true (P)ositive (F)eedback parameter for the Tsetlini model, default=" + std::to_string(boost_tpf)),
        clipp::option("--tsetlini-max-weight", "-w").doc("Max weight parameter for the Tsetlini model") & clipp::value(is_natural(), "max_weight=" + std::to_string(ts_max_weight), ts_max_weight),
        clipp::option("--tsetlini-jobs", "-j").doc("Number of jobs parameter for the Tsetlini model") & clipp::value("jobs=" + std::to_string(ts_njobs), ts_njobs),
        clipp::option("--nepochs").doc("Number of epochs for each call to fit()") & clipp::value(is_natural(), "nepochs=" + std::to_string(nepochs), nepochs)
    );

    auto cli = (inference | training);

    if (not clipp::parse(argc, argv, cli))
    {
        std::cout << clipp::make_man_page(cli, argv[0]);
    }
    else
    {
        spdlog::info("Start");

        if (do_infer)
        {
            spdlog::info("Inference");

            if (bad_filename(csv_ifname)
                or bad_filename(encoder_ifname)
                or bad_filename(model_ifname))
            {
                std::exit(1);
            }

            infer(csv_ifname, encoder_ifname, model_ifname);
        }
        else
        {
            spdlog::info("Training");

            if (bad_filename(csv_ifname)
                or bad_filename(encoder_ifname))
            {
                std::exit(1);
            }

            model_params_t const model_params{
                {"threshold", ts_threshold},
                {"s", ts_s},
                {"clauses", ts_clauses},
                {"boost_tpf", boost_tpf},
                {"max_weight", ts_max_weight},
                {"nepochs", nepochs},
                {"n_jobs", ts_njobs}
            };

            train(csv_ifname, encoder_ifname, model_ifname, model_params);
        }
    }

    return 0;
}
