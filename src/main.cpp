#include <InSDL.hpp>
#include <save.hpp>

using namespace std;

string path = "Z:/cpp/clicker/";
string font = path + "font.ttf";

int main() {
    int count = 0, clicker = 1, upgPrice = 100;

    // Инициализация и загрузка данных
    loadGame(count, clicker, upgPrice);

    app game;
    game.init(500, 700, "Clicker", true);
    game.setIcon(texture(game.Render, path + "image/icon.bmp"));

    // Основной блок по которому кликать
    frect block((game.window.width - 200) / 2, (game.window.height - 200) / 2, 200, 200);
    texture blockTexture(game.Render, path + "image/empty.bmp");

    // Текстовые элементы
    text counterText(game.Render, to_string(count).c_str(), font);
    frect counter((game.window.width - 40) / 2, (game.window.height - 80) / 2 + 170, 40, 80);

    text levelText(game.Render, ("level: " + to_string(clicker)).c_str(), font);
    frect level((game.window.width - 280) / 2, 100, 280, 100);

    text priceText(game.Render, ("price: " + to_string(upgPrice)).c_str(), font);
    frect price((game.window.width - 80) / 2, (game.window.height - 40) / 2 + 330, 80, 20);

    // Кнопка улучшения
    frect upgradeButton((game.window.width - 200) / 2, (game.window.height - 70) / 2 + 270, 200, 70);
    texture upgradeButtonTexture(game.Render, path + "image/upg_btn.bmp");

    // Обработка кликов
    game.bindMouseButton(SDL_BUTTON_LEFT, [&]() {
        if (block.onHover()) {
            counterText.setText(to_string(count += clicker).c_str());
        }

        if (upgradeButton.onHover() && count >= upgPrice) {
            count -= upgPrice;
            clicker++;
            upgPrice = static_cast<int>(upgPrice * 1.5);

            levelText.setText(("level: " + to_string(clicker)).c_str());
            counterText.setText(to_string(count).c_str());
            priceText.setText(("price: " + to_string(upgPrice)).c_str());

            counter.setWidth(40 * to_string(count).size());
            counter.setX((game.window.width - counter.getWidth()) / 2);
        }
    });

    // Основной цикл
    while (!game.quit) {
        handleEvent(game);

        // Центрирование текста
        counter.setWidth(40 * to_string(count).size());
        counter.setX((game.window.width - counter.getWidth()) / 2);

        // Рендер элементов
        game.fill(201, 192, 187);
        block.fillTexture(game.Render, &blockTexture);
        upgradeButton.fillTexture(game.Render, &upgradeButtonTexture);
        level.fillText(game.Render, &levelText);
        counter.fillText(game.Render, &counterText);
        price.fillText(game.Render, &priceText);

        // Анимация при наведении
        block.setSize(block.onHover() ? 220 : 200, block.onHover() ? 220 : 200);
        upgradeButton.setSize(upgradeButton.onHover() ? 210 : 200, upgradeButton.onHover() ? 80 : 70);

        // Центрирование
        block.setPosition((game.window.width - block.getWidth()) / 2, 
                          (game.window.height - block.getHeight()) / 2);
        upgradeButton.setPosition((game.window.width - upgradeButton.getWidth()) / 2, 
                                  (game.window.height - upgradeButton.getHeight()) / 2 + 270);

        game.update();
    }

    saveGame(count, clicker, upgPrice);
    game.exit();
    return 0;
}