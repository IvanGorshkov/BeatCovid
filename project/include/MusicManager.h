#pragma once

#include "SFML/Audio.hpp"

class MusicManager {
 public:
  MusicManager();
  void PlayBackgroundGameMusic();
  void PlayBackgroundMenuMusic();
  void PlayHitPlayerSound();
  void PlayHitEnemySound();
  void PlayDiedEnemySound();
  void PlayTransportSound();
  void PlayWalkPlayerSound();
  void PlayJumpPlayerSound();
  void PlayGetAntibodiesSound();
  void PlayGetVaccineSound();
  void PlayTreatPatientSound();

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

  // Движение трансопрта
  sf::SoundBuffer transportBuffer;
  sf::Sound transportSound;

  // Движение игрока
  sf::SoundBuffer walkPlayerBuffer;
  sf::Sound walkPlayerSound;

  // Прыжок игрока
  sf::SoundBuffer jumpPlayerBuffer;
  sf::Sound jumpPlayerSound;

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