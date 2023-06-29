/**
 * @file
 * @brief Defines the CrossRefAPI class for interacting with the CrossRef API.
 */

#ifndef SCIENCEPARSER_CROSSREFAPI_HPP
#define SCIENCEPARSER_CROSSREFAPI_HPP

#include "API.hpp"
#include "Articles.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <cpr/cpr.h>

using Json::Value;

/**
 * @brief Представляет класс API CrossRef, который расширяет класс AbstractAPI.
 */
class CrossRefAPI : public AbstractAPI {
private:
    std::string root = "https://api.crossref.org"; /**< Корневой URL-адрес для CrossRef API. */
    std::map<std::string, std::string> routes = {{"getArticle", "/works/"}}; /**< Маршруты для разных конечных точек API. */

public:
    /**
     * @brief Извлекает статью по ее DOI (цифровому идентификатору объекта).
     * @param DOI DOI статьи
     * @return Объект Article, содержащий информацию о статье.
     */
    Article getArticleByDOI(const std::string& DOI) override {

        std::string url = root + routes["getArticle"] + DOI;

        cpr::Response response = cpr::Get(cpr::Url(url));

        Value title = "no info";
        Value publisher = "no info";
        Value cited = -1;

        std::vector<SimpleArticle> references = {};

        Value message;
        Value data;
        Value tmp;

        if (response.status_code == 200) {
            Json::Reader reader;
            reader.parse(response.text, data);

            if (data.get("status", "fail") == "ok") {
                message = data.get("message", Value());

                tmp = message.get("title", Value());
                if (tmp.isArray() && !tmp.empty()) {
                    title = tmp[0].asString();
                }

                publisher = message.get("publisher", "no info");
                cited = message.get("is-referenced-by-count", -1);

                tmp = message.get("reference", Value());

                if (tmp.isArray()) {
                    for (const auto &element: tmp) {
                        SimpleArticle art {
                                element.get("DOI", "no info").asString(),
                                element.get("unstructured", "no info").asString()
                        };
                        references.push_back(art);
                    }
                }
            }
        }

        Article art;
        art.doi = DOI;
        art.title = title.asString();
        art.unstructured = title.asString();
        art.publisher = publisher.asString();
        art.cited = cited.asInt();
        art.references = references;
        art.statusCode = response.status_code;

        return art;
    };

    /**
     * @brief Геттер для получения корневого URL-адреса API.
     * @return Корневой URL-адрес API.
     */
    std::string getRoot() const override {
        return root;
    }

    /**
     * @brief Геттер для получения маршрутов, доступных в API.
     * @return Map маршрутов, доступная в API.
     */
    std::map<std::string, std::string> getRoutes() const override {
        return routes;
    }

    CrossRefAPI() = default;
    ~CrossRefAPI() = default;
};

#endif // SCIENCEPARSER_CROSSREFAPI_HPP