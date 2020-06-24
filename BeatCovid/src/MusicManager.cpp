#include "MusicManager.h"
#include "ResourcePath.hpp"

MusicManager::MusicManager()
    : isDriveMetro(false),
      isDriveCar(false) {
  backgroundGameMusic.openFromFile(resourcePath() + "files/music/gameBack.wav");
  backgroundMenuMusic.openFromFile(resourcePath() + "files/music/menuBack.wav");

  hitPlayerBuffer.loadFromFile(resourcePath() + "files/music/playerHit.wav");
  hitPlayerSound.setBuffer(hitPlayerBuffer);

  hitEnemyBuffer.loadFromFile(resourcePath() + "files/music/enemyHit.wav");
  hitEnemySound.setBuffer(hitEnemyBuffer);

  diedEnemyBuffer.loadFromFile(resourcePath() + "files/music/enemyDie.wav");
  diedEnemySound.setBuffer(diedEnemyBuffer);

  diedPlayerBuffer.loadFromFile(resourcePath() + "files/music/playerDie.wav");
  diedPlayerSound.setBuffer(diedPlayerBuffer);

  metroBuffer.loadFromFile(resourcePath() + "files/music/metroSound.wav");
  metroSound.setBuffer(metroBuffer);

  carBuffer.loadFromFile(resourcePath() + "files/music/carSound.wav");
  carSound.setBuffer(carBuffer);

//  walkPlayerBuffer.loadFromFile(resourcePath() + "files/music/1.wav");
//  walkPlayerSound.setBuffer(walkPlayerBuffer);
//
//  jumpPlayerBuffer.loadFromFile(resourcePath() + "files/music/1.wav");
//  jumpPlayerSound.setBuffer(jumpPlayerBuffer);

  getAntibodiesBuffer.loadFromFile(resourcePath() + "files/music/getAntibodies.wav");
  getAntibodiesSound.setBuffer(getAntibodiesBuffer);

  getVaccineBuffer.loadFromFile(resourcePath() + "files/music/getVaccine.wav");
  getVaccineSound.setBuffer(getVaccineBuffer);

  treatPatientBuffer.loadFromFile(resourcePath() + "files/music/treatPatient.wav");
  treatPatientSound.setBuffer(treatPatientBuffer);
}

void MusicManager::PlayBackgroundGameMusic() {
  backgroundMenuMusic.stop();
  backgroundGameMusic.setVolume(4);
  backgroundGameMusic.setLoop(true);
  backgroundGameMusic.play();
}

void MusicManager::StopBackgroundGameMusic() {
  backgroundGameMusic.stop();
}

void MusicManager::PlayBackgroundMenuMusic() {
  backgroundGameMusic.stop();
  backgroundMenuMusic.setVolume(10);
  backgroundMenuMusic.setLoop(true);
  backgroundMenuMusic.play();
}

void MusicManager::StopBackgroundMenuMusic() {
  backgroundMenuMusic.stop();
}

void MusicManager::PlayHitPlayerSound() {
  hitPlayerSound.setVolume(10);
  hitPlayerSound.play();
}

void MusicManager::PlayHitEnemySound() {
  hitEnemySound.setVolume(10);
  hitEnemySound.play();
}

void MusicManager::PlayDiedEnemySound() {
  diedEnemySound.setVolume(10);
  diedEnemySound.play();
}

void MusicManager::PlayDiedPlayerSound() {
  backgroundGameMusic.stop();
  diedPlayerSound.setVolume(10);
  diedPlayerSound.play();
}

void MusicManager::PlayMetroSound() {
  isDriveMetro = !isDriveMetro;

  if (isDriveMetro) {
    metroSound.setVolume(10);
    metroSound.setLoop(true);
    metroSound.play();
  } else {
    metroSound.stop();
  }
}

void MusicManager::PlayCarSound() {
  isDriveCar = !isDriveCar;

  if (isDriveCar) {
    carSound.setVolume(10);
    carSound.setLoop(true);
    carSound.play();
  } else {
    carSound.stop();
  }
}

void MusicManager::PlayWalkPlayerSound() {
  walkPlayerSound.setVolume(10);
  walkPlayerSound.play();
}

void MusicManager::PlayJumpPlayerSound() {
  jumpPlayerSound.setVolume(10);
  jumpPlayerSound.play();
}

void MusicManager::PlayGetAntibodiesSound() {
  getAntibodiesSound.setVolume(10);
  getAntibodiesSound.play();
}

void MusicManager::PlayGetVaccineSound() {
  getVaccineSound.setVolume(10);
  getVaccineSound.play();
}

void MusicManager::PlayTreatPatientSound() {
  treatPatientSound.setVolume(10);
  treatPatientSound.play();
}

void MusicManager::StopTreatPatientSound() {
  treatPatientSound.stop();
}
