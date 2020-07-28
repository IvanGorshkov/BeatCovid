#pragma once

#include "SFML/Audio.hpp"

#define BACK_MENU 50
#define ON_BUTTON 15
#define SELECT_BUTTON 20
#define BACK_GAME 0
#define HIT_PLAYER 70
#define HIT_ENEMY 70
#define DIED_ENEMY 70
#define DIED_PLAYER 70
#define METRO 70
#define CAR 70
#define ANTIBODIES 70
#define VACCINE 70
#define TREAT_PATIENT 70

class MusicManager {
 public:
  MusicManager();
  void PlayBackgroundMenuMusic();
  void StopBackgroundMenuMusic();
  void PlayOnButtonSound();
  void PlaySelectButtonSound();
    
  void PlayBackgroundGameMusic();
  void StopBackgroundGameMusic();
  void PlayHitPlayerSound();
  void PlayHitEnemySound();
  void PlayDiedEnemySound();
  void PlayDiedPlayerSound();
  void PlayMetroSound();
  void PlayCarSound();
  void StopCarSound();
  void PlayGetAntibodiesSound();
  void PlayGetVaccineSound();
  void PlayTreatPatientSound();
  void StopTreatPatientSound();

  void StopAllMusic();

 private:
  // Звук меню
  sf::Music backgroundMenuMusic;
    
  // Наведение на кнопку
  sf::SoundBuffer onButtonBuffer;
  sf::Sound onButtonSound;
    
  // Выбор кнопки
  sf::SoundBuffer selectButtonBuffer;
  sf::Sound selectButtonSound;
    
  // Звук игры
  sf::Music backgroundGameMusic;

  // Стрельба игроком
  sf::SoundBuffer hitPlayerBuffer;
  sf::Sound hitPlayerSound;

  // Стрельба врагом
  sf::SoundBuffer hitEnemyBuffer;
  sf::Sound hitEnemySound;

  // Смерть врага
  sf::SoundBuffer diedEnemyBuffer;
  sf::Sound diedEnemySound;

  // Смерть игрока
  sf::SoundBuffer diedPlayerBuffer;
  sf::Sound diedPlayerSound;

  // Движение поезда
  sf::SoundBuffer metroBuffer;
  sf::Sound metroSound;
  bool isDriveMetro;

  // Движение машин
  sf::SoundBuffer carBuffer;
  sf::Sound carSound;
  bool isDriveCar;

  // Получение антител
  sf::SoundBuffer getAntibodiesBuffer;
  sf::Sound getAntibodiesSound;

  // Получение вацины
  sf::SoundBuffer getVaccineBuffer;
  sf::Sound getVaccineSound;

  // Лечение пациена
  sf::SoundBuffer treatPatientBuffer;
  sf::Sound treatPatientSound;
};
