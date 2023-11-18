#ifndef H_STATE_LOGIN_FORM
#define H_STATE_LOGIN_FORM

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateLoginForm : public AppState
  {
  private:
    FluffyMultiplayer::LoginFormData form_data;
    std::array<std::string,5> label_text;

    std::array<sf::Text,9> labels;
    sf::Texture button_sprite;
    std::array<sf::Sprite, 2> text_input_sprite;
    std::array<sf::Sprite, 2> button_sprites;
    sf::Texture text_input_texture;
    sf::Texture login_texture;
    std::array<sf::Texture, 2> saveLoginCheckBox_textures;
    std::array<sf::Texture, 2> showPassword_texutres;
    sf::Sprite showPassword_sprite;
    sf::Sprite saveLoginCheckBox_sprite;
    std::array<sf::FloatRect, 6> form_boundaries;

    void initFormLabels();
  public:
    StateLoginForm();
    StateLoginForm(FluffyMultiplayer::LoginFormData); //if form failed re-fills form automatically
    ~StateLoginForm();

    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
