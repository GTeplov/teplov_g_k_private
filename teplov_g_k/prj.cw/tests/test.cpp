#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <string>
#include <scienceParser/Articles.hpp>
#include <scienceParser/CrossRefAPI.hpp>
#include <vector>
#include <iostream>

TEST_CASE("testing the CrossRef") {

    CrossRefAPI api = CrossRefAPI();
    Article clear = Article();

    clear.doi = "10.111/afsfafa";
    clear.statusCode = 404;

    // unknown article check
    Article bad = api.getArticleByDOI("10.111/afsfafa");
    CHECK(clear == bad);

    std::vector <SimpleArticle> list = {
            SimpleArticle{ "10.1063/1.1378340", "no info"},
            SimpleArticle{},
            SimpleArticle{ "10.1063/1.1957118", "no info"},
            SimpleArticle{ "10.1021/nl060331v", "no info"},
            SimpleArticle{ "10.1103/PhysRevLett.87.215502", "no info"},
            SimpleArticle{ "10.1115/1.1597619", "no info"},
            SimpleArticle{ "10.1063/1.1616981", "no info"},
            SimpleArticle{ "10.1088/0022-3727/39/15/021", "no info"},
            SimpleArticle{ "10.1063/1.2199614", "no info"},
            SimpleArticle{ "10.1063/1.2402973", "no info"},
            SimpleArticle{ "10.1201/9780429258367", "J. V. Beck, K. D. Cole, A. Haji-Sheikh, and B. Litkouhi, inHeat Conduction Using Green’s Functions(Hemisphere, New York, 1992), p. 482."},
            SimpleArticle{ "10.1063/1.1728417", "no info"},
            SimpleArticle{ },
            SimpleArticle{ "no info", "R. Weast,Handbook of Chemistry and Physics, 64th ed. (CRC, Boca Raton, Florida, 1983), p. F–125."},
            SimpleArticle{ "10.1002/1521-4095(200008)12:16<1190::AID-ADMA1190>3.3.CO;2-3", "no info"},
            SimpleArticle{ "no info", "C. Kittel, inIntroduction to Solid State Physics, 5th ed. (Wiley, New York, 1976), p. 178."},
            SimpleArticle{ "10.1088/0022-3727/34/15/302", "no info"}};

    Article test = Article{"10.1063/1.2714679",
                           "Thermal characterization of microscale conductive and nonconductive wires using transient electrothermal technique",
                           "Thermal characterization of microscale conductive and nonconductive wires using transient electrothermal technique",
                           "AIP Publishing",
                           128,
                           list
                           };

    Article byDoi = api.getArticleByDOI("10.1063/1.2714679");

    // parser test
    CHECK(test == byDoi);

}