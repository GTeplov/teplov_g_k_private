#include <scienceParser/CrossRefAPI.hpp>
#include <scienceParser/Articles.hpp>
#include <iostream>
#include <string>

int main() {
    CrossRefAPI api = CrossRefAPI();

    std::string doi = "10.1038/nature12373";

    Article art = api.getArticleByDOI(doi);

    std::cout << "title: " << art.title << std::endl;
    std::cout << "doi: " << art.doi << std::endl;
    std::cout << "publisher: " << art.publisher << std::endl;
    std::cout << "cited: " << art.cited << std::endl;
    std::cout << "references count: " << art.references.size() << std::endl;

    std::cout << "Press ENTER for exit" << std::endl;
    std::cin.get();

    return 0;
}