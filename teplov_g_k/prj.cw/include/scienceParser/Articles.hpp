/**
 * @file
 * @brief Определяет сущности описывающие статью в кратком и полном виде и связанные с ними функции.
 */

#ifndef SCIENCEPARSER_CPP_ARTICLE_HPP
#define SCIENCEPARSER_CPP_ARTICLE_HPP


#include <string>
#include <vector>
#include <regex>


/**
 * @brief Представляет собой сущность упрощенно описывающую статью.
 */
struct SimpleArticle {
    std::string doi = "no info"; /**< DOI (цифровой идентификатор объекта) статьи. */
    std::string unstructured = "no info"; /**< Неструктурированная информация о статье. */

    /**
     * @brief Перегружает оператор равенства (==) для сравнения двух объектов SimpleArticle.
     * @param other The SimpleArticle объект для сравнения.
     * @return true, если два объекта SimpleArticle равны, в противном случае false.
     */
    bool operator==(const SimpleArticle& other) const {
        return (doi == other.doi) &&
               (unstructured == other.unstructured);
    }

    /**
    * @brief Перегружает оператор равенства (!=) для сравнения двух объектов SimpleArticle.
    * @param other The SimpleArticle объект для сравнения.
    * @return true, если два объекта SimpleArticle не равны, в противном случае false.
    */
    bool operator!=(const SimpleArticle& other) const {
        return !(*this == other);
    }
};


/**
 * @brief Представляет собой сущность описывающую статью.
 */
struct Article : SimpleArticle {
    std::string title = "no info"; /**< Название статьи. */
    std::string publisher = "no info"; /**< Издатель статьи. */
    int cited = -1; /**< Количество цитирований статьи. */
    std::vector<SimpleArticle> references = {}; /**< Список литературы (DOI) к статье. */
    int statusCode = 200; /**< Код состояния HTTP, указывающий статус поиска статьи. */

    /**
     * @brief Перегружает оператор равенства (==) для сравнения двух объектов Article.
     * @param other The Article объект для сравнения.
     * @return true, если два объекта Article равны, в противном случае false.
     */
    bool operator==(const Article &other) const {
        return (title == other.title) &&
                (doi == other.doi) &&
                (unstructured == other.unstructured) &&
                (publisher == other.publisher) &&
                (cited == other.cited) &&
                (references == other.references);
    }

    /**
     * @brief Перегружает оператор равенства (!=) для сравнения двух объектов Article.
     * @param other The Article объект для сравнения.
     * @return true, если два объекта Article не равны, в противном случае false.
     */
    bool operator!=(const Article &other) const {
        return !(*this == other);
    }
};


/**
 * @brief Проверяет, является ли введенная строка допустимым DOI (идентификатором цифрового объекта).
 * @param DOI Строка для проверки.
 * @return true, если строка является допустимым DOI, в противном случае false.
 */
bool isDOI(const std::string& DOI) {
    std::regex doiReg("^10\\.\\d{4,9}/[-._;()/:a-zA-Z0-9]+$", std::regex::icase);

    return std::regex_match(DOI, doiReg);
}

#endif //SCIENCEPARSER_CPP_ARTICLE_HPP