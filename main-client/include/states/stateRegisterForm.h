#ifndef H_STATE_REGISTER_FORM
#define H_STATE_REGISTER_FORM

#include "../appState.h"

namespace FluffyMultiplayer
{
  class App; // Forward declaration of App class
  class AppState; // Forward declaration of AppState class

  class StateRegisterForm : public AppState
  {
  private:
    std::array<std::string,5> label_text;

    FluffyMultiplayer::RegisterFormData form_data;
    void initForm();

    std::array<sf::Text,3> input_lables;
    std::array<sf::Sprite,3> input_sprite;
    std::array<sf::Text,6> form_labels;
  public:
    StateRegisterForm();
    StateRegisterForm(FluffyMultiplayer::RegisterFormData);
    ~StateRegisterForm();
    void render(sf::RenderWindow&);
    FluffyMultiplayer::AppState* update(FluffyMultiplayer::App&,
                      std::queue<std::string>&,
                      std::queue<std::string>&);
    FluffyMultiplayer::AppState* eventHandle(FluffyMultiplayer::App&,
                              sf::Event&);
  };
}

#endif
