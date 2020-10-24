#if defined __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include <string>

std::string filename(std::string const & path)
{
    return fs::path(path).filename();
}
