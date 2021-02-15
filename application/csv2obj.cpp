#include "CurveExtruder.hpp"

#include "ArgsPerser.hpp"

#include <filesystem>
#include <string>



int main(int argc, char* argv[]) {
    auto argParser = BasicUtl::ArgsParser();
    argParser.setUsage("csv2obj [OPTION] ... <CSV file path>");
    argParser.setOption('e', "extrude", 
        "Extrude given csv to given length"
    );
    argParser.setOption('l', "length",
        "Length of extrusion. if skip this option, target will be 1 (unit) extruded.",
        true
    );
    argParser.setOption('s', "surface",
        "The surface to place a outline curve by csv.",
        true 
    );

    argParser.parse(argc, argv);

    if (argParser.exists("e")) {
        using Surface = STool::CurveExtruder::Surface;

        // Get options and their arguments.
        auto length = argParser.exists("l")? 
            argParser.getValue<double>("l"): 
            1.0;
        auto surface = argParser.exists("s")? 
            argParser.getValue<Surface>("s", STool::CurveExtruder::makeSurface): 
            Surface::xy;
        auto args = argParser.getArgs();

        // Get required arguments.
        auto csvPath = std::filesystem::path(args[0]);
        auto objPath = std::filesystem::current_path();

        // Extrusion of CSV.
        CTool::DoubleSV csv(csvPath);
        STool::CurveExtruder extruder(STool::Curve2D(csv, true), surface);

        auto obj = extruder.extrude(length);
        obj.output(objPath);
    }

    return 0;
}
