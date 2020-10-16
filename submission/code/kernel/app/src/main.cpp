#include "model_params.hpp"
#include "infer.hpp"
#include "train.hpp"

#include "clipp.hpp"

#include <iostream>


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


int main(int argc, char **argv)
{
    float ts_s = 4.0;
    unsigned int ts_clauses = 3200;
    int ts_njobs = 2;
    int ts_max_weight = std::numeric_limits<int>::max();
    bool boost_tpf = true;
    std::string model_ifname;
    std::string csv_ifname;
    std::string encoder_ifname;
    bool do_infer = false;

    auto cli = (
        clipp::option("--infer").set(do_infer).doc("Request inference instead of training"),

        clipp::option("--model", "-m").doc("Pre-trained input model to load") & clipp::value("JSON-ized model file to read from", model_ifname),
        clipp::option("--datafile", "-d").doc("Input CSV file for training or inference") & clipp::value("CSV data file to read from", csv_ifname),
        clipp::option("--encoding", "-e").doc("Input JSON file with input encoding parameters") & clipp::value("JSON encoding file to read from", encoder_ifname),

        clipp::option("--tsetlini-s", "-s").doc("Specificity parameter for the Tsetlini model") & clipp::value("s=" + std::to_string(ts_s), ts_s),
        clipp::option("--tsetlini-clauses", "-C").doc("Number of clauses parameter for the Tsetlini model") & clipp::value(is_natural(), "clauses=" + std::to_string(ts_clauses), ts_clauses),
        (
            clipp::option("--tsetlini-boost-tpf", "-B").set(boost_tpf, true) |
            clipp::option("--tsetlini-no-boost-tpf", "-b").set(boost_tpf, false)
        ).doc("Boost (T)true (P)ositive (F)eedback parameter for the Tsetlini model, default=" + std::to_string(boost_tpf)),
        clipp::option("--tsetlini-max-weight", "-w").doc("Max weight parameter for the Tsetlini model") & clipp::value(is_natural(), "max_weight=" + std::to_string(ts_max_weight), ts_max_weight),
        clipp::option("--tsetlini-jobs", "-j").doc("Number of jobs parameter for the Tsetlini model") & clipp::value("jobs=" + std::to_string(ts_njobs), ts_njobs)
    );

    if (not clipp::parse(argc, argv, cli))
    {
        std::cout << clipp::make_man_page(cli, argv[0]);
    }
    else
    {
        if (do_infer)
        {
            infer(csv_ifname, encoder_ifname, model_ifname);
        }
        else
        {
            model_params_t const model_params{
                {"s", ts_s},
                {"clauses", ts_clauses},
                {"boost_tpf", boost_tpf},
                {"max_weight", ts_max_weight},
                {"n_jobs", ts_njobs}
            };

            train(csv_ifname, encoder_ifname, model_ifname, model_params);
        }
    }

    return 0;
}
