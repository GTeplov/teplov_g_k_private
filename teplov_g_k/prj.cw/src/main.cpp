#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <scienceParser/Articles.hpp>
#include <scienceParser/CrossRefAPI.hpp>



using std::vector;
using std::string;
using std::pair;


constexpr char replaceLine[] = "\r                                                                                                            \r";

struct OutLine {
    string doi;
    string unstructured;
    int cided;
};

struct Args {
    std::string input = "";
    std::string output = "";
    bool showHelp = false;
};

bool fileExists(const string& filePath) {
    std::ifstream file(filePath);

    return file.good();
}

void saveCSV(const std::string& path, const vector<OutLine>& data) {
    std::ofstream file;
    file.open(path);

    file << "doi" << "," << "title" << "," << "citised" << "\n";

    for (const auto &element: data)
        if (element.unstructured != "no info" && element.doi != "no info")
            file << element.doi << "," << element.unstructured << "," <<element.cided << "\n";

    file.close();

}

void printHelp() {
    std::cout << "Usage: scienceParser-test-app -i/--input <input_file> -o/--output <output_file>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i, --input    Input file with DOI's from a new line or string with DOI like '***/*****'" << std::endl;
    std::cout << "  -o, --output   Output CSV file with DOI's" << std::endl;
    std::cout << "  -h, --help     Show help message" << std::endl << std::endl;

    std::cout << "For example:" << std::endl;
    std::cout << "\tscienceParser-test-app -i 10.1063/1.1616981 -o out.csv" << std::endl;
    std::cout << "Or" << std::endl;
    std::cout << "\tscienceParser-test-app -i in.txt -o out.csv" << std::endl;

}

Args parseArguments(const int& argc, char* argv[]) {
    Args args;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-i" || arg == "--input") {
            if (i + 1 < argc) {
                args.input = argv[++i];
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                args.output = argv[++i];
            }
        } else if (arg == "-h" || arg == "--help") {
            args.showHelp = true;

            // stop parse args if found help.
            break;
        }
    }

    return args;
}

int main(int argc, char* argv[]) {
    // parse input arguments cli
    Args args = parseArguments(argc, argv);
    CrossRefAPI api = CrossRefAPI();

    if (args.showHelp) {
        printHelp();
        return 0;
    }

    if (args.input == "" || args.output == "") {
        std::cout << "Missing required arguments. Use --help for more information." << std::endl;
        return 1;
    }

    vector<OutLine> data = {};

    if (fileExists(args.input)) {
        int lineCount = 0;
        std::ifstream file(args.input);
        if (file.is_open()) {
            string line;

            while (std::getline(file, line)) {
                ++lineCount;
                if (! isDOI(line))
                    std::cout << replaceLine << lineCount << " skiped bad DOI: " << line;
                else {
                    std::cout << replaceLine << lineCount << " Recive info for input article. DOI: " << line;

                    // for skip \r line
                    std::cout << std::endl;

                    Article article = api.getArticleByDOI(line);

                    if (article == Article())
                        std::cout << replaceLine << "Info not found on CrossRef for DOI: " << line;

                    else if (article.statusCode != 200)
                        std::cout << std::endl << "Failed get request. Status code: " << article.statusCode;

                    else {
                        int refCount = 0;

                        for(const auto &reference: article.references) {
                            std::cout << replaceLine << ++refCount << " Recive info for DOI: " << reference.doi;
                            Article subArticle = api.getArticleByDOI(reference.doi);

                            if (subArticle == Article())
                                std::cout << replaceLine << "Info not found on CrossRef for DOI: " << line;

                            else if(subArticle.statusCode != 200)
                                std::cout << std::endl << "Failed get request. Status code: " << subArticle.statusCode;

                            else
                                data.push_back(OutLine{subArticle.doi,
                                                       subArticle.title != "no info" ?
                                                       subArticle.title : subArticle.unstructured,
                                                       subArticle.cited});
                        }

                        // for skip \r line
                        std::cout << std::endl;
                    }

                }

                // for skip \r line
                std::cout << std::endl;
            }

            file.close();

            // sort by count by the number of citations
            std::sort(data.begin(), data.end(), [](OutLine first, OutLine second){
                return first.cided > second.cided;
            });

            std::cout << "Save output to " << args.output << std::endl;

            saveCSV(args.output, data);

        } else {
            std::cout << "Unable to open file: " << args.input << std::endl;

            return 1;
        }

    }
    else if (isDOI(args.input)) {
        std::cout << replaceLine << " Recive info for input article. DOI: " << args.input;

        Article article = api.getArticleByDOI(args.input);

        if (article == Article())
            std::cout << replaceLine << "Info not found on CrossRef for DOI: " << args.input;

        else if (article.statusCode != 200)
            std::cout << std::endl << "Failed get request. Status code: " << article.statusCode;

        else {
            int refCount = 0;

            for(const auto &reference: article.references) {
                std::cout << replaceLine << ++refCount << " Recive info for DOI: " << reference.doi;
                Article subArticle = api.getArticleByDOI(reference.doi);

                if (subArticle == Article())
                    std::cout << replaceLine << "Info not found on CrossRef for DOI: " << args.input;

                else if(subArticle.statusCode != 200)
                    std::cout << std::endl << "Failed get request. Status code: " << subArticle.statusCode;

                else
                    data.push_back(OutLine{subArticle.doi,
                                           subArticle.title != "no info" ?
                                           subArticle.title : subArticle.unstructured,
                                           subArticle.cited});
            }

            // for skip \r line
            std::cout << std::endl;

            // sort by count by the number of citations
            std::sort(data.begin(), data.end(), [](OutLine first, OutLine second){
                return first.cided > second.cided;
            });

            std::cout << "Save output to " << args.output << std::endl;

            saveCSV(args.output, data);
        }

    }
    else {
        std::cout << args.input << " is neither a file name nor a DOI" << std::endl;
        return 0;
    }

    std::cout << "Press ENTER for exit" << std::endl;
    std::cin.get();

    return 0;
}