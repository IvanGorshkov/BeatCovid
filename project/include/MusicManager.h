#pragma once

#include "SFML/Audio.hpp"

class MusicManager {
 public:
  MusicManager();
  void PlayBackgroundGameMusic();
  void StopBackgroundGameMusic();
  void PlayBackgroundMenuMusic();
  void StopBackgroundMenuMusic();
  void PlayHitPlayerSound();
  void PlayHitEnemySound();
  void PlayDiedEnemySound();
  void PlayDiedPlayerSound();
  void PlayMetroSound();
  void PlayCarSound();
  void PlayGetAntibodiesSound();
  void PlayGetVaccineSound();
  void PlayTreatPatientSound();
  void StopTreatPatientSound();

 private:
  // Звук игры
  sf::Music backgroundGameMusic;

  // Звук меню
  sf::Music backgroundMenuMusic;

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
