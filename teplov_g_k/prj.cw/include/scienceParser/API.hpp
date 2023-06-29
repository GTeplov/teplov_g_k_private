/**
 * @file
 * @brief Определяет абстрактный класс API для доступа к API-интерфейсам для поиска научных статей.
 */


#ifndef SCIENCEPARSER_API_HPP
#define SCIENCEPARSER_API_HPP

#include <string>
#include <vector>
#include <map>
#include "Articles.hpp"


/**
 * @class AbstractAPI
 * @brief Абстрактный базовый класс, представляющий API.
 *
 * Этот класс предоставляет абстрактный интерфейс для доступа к API для анализа информации научных статей.
 * Он определяет общие методы и переменные-члены, которые могут реализовывать производные классы.
 */
class AbstractAPI {
private:
    std::string root = ""; /**< Корневой URL-адрес API. */
    std::map <std::string, std::string> routes = {{"getArticle", ""}}; /**< Map маршрутов доступна в API. */

public:
    /**
     * @brief Найдите статью по ее DOI.
     * @param DOI DOI статьи, которую нужно извлечь.
     * @return Объект Article, представляющий статью.
     *
     * Это виртуальный метод, который должен быть реализован производными классами.
     * Он извлекает статью из API на основе предоставленного DOI.
     */
    virtual Article getArticleByDOI(const std::string& DOI) {
        return Article();
    }

    /**
     * @brief Геттер для получения корневого URL-адреса API.
     * @return Корневой URL-адрес API.
     *
     * Это чисто виртуальный метод, который должен быть реализован производными классами.
     * Он возвращает корневой URL-адрес API.
     */
    virtual std::string getRoot() const = 0;

    /**
     * @brief Геттер для получения маршрутов, доступных в API.
     * @return Map маршрутов, доступная в API.
     *
     * Это чисто виртуальный метод, который должен быть реализован производными классами.
     * Он возвращает Map маршрутов, доступных в API, где каждый маршрут представлен парой ключ-значение.
     */
    virtual std::map <std::string, std::string> getRoutes() const = 0;

    /**
     * @brief Виртуальный деструктор.
     *
     * Это виртуальный деструктор, обеспечивающий надлежащую очистку при уничтожении объектов производных классов.
     */
    virtual ~AbstractAPI() {};
};

#endif //SCIENCEPARSER_API_HPP
