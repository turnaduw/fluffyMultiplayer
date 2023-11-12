#ifndef H_STATE_LOGIN_FORM
#define H_STATE_LOGIN_FORM

#include "../appState.h"
#include "../app.h"

namespace FluffyMultiplayer
{
  class StateLoginForm : public AppState
  {
  private:
    std::array<std::string,2> form_errors;
    std::array<std::string,2> form_inputs;
    std::array<std::string,6> label_text;
    std::array<sf::Text,10> labels;
    sf::Texture button_sprite;
    std::array<sf::Sprite, 2> text_input_sprite;
    std::array<sf::Sprite, 2> button_sprites;
    sf::Texture text_input_texture;
    bool saveLoginStatus;
    sf::Texture login_texture;
    std::array<sf::Texture, 2> saveLoginCheckBox_textures;
    std::array<sf::Texture, 2> showPassword_texutres;
    sf::Sprite showPassword_sprite;
    sf::Sprite saveLoginCheckBox_sprite;
    std::array<sf::FloatRect, 6> form_boundaries;

  public:
    StateLoginForm();
    StateLoginForm( std::array<std::string, 2>inputs, std::array<std::string, 2>errors, bool rememberlogin );
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
