#include "MusicManager.h"
#include "iostream"

MusicManager::MusicManager()
    : isDrive(false) {
  backgroundGameMusic.openFromFile("../files/music/1.wav");
  backgroundMenuMusic.openFromFile("../files/music/1.wav");

  hitPlayerBuffer.loadFromFile("../files/music/1.wav");
  hitPlayerSound.setBuffer(hitPlayerBuffer);

  hitEnemyBuffer.loadFromFile("../files/music/1.wav");
  hitEnemySound.setBuffer(hitEnemyBuffer);

  diedEnemyBuffer.loadFromFile("../files/music/1.wav");
  diedEnemySound.setBuffer(diedEnemyBuffer);

  transportBuffer.loadFromFile("../files/music/1.wav");
  transportSound.setBuffer(transportBuffer);

  walkPlayerBuffer.loadFromFile("../files/music/1.wav");
  walkPlayerSound.setBuffer(walkPlayerBuffer);

  jumpPlayerBuffer.loadFromFile("../files/music/1.wav");
  jumpPlayerSound.setBuffer(jumpPlayerBuffer);

  getAntibodiesBuffer.loadFromFile("../files/music/1.wav");
  getAntibodiesSound.setBuffer(getAntibodiesBuffer);

  getVaccineBuffer.loadFromFile("../files/music/1.wav");
  getVaccineSound.setBuffer(getVaccineBuffer);

  treatPatientBuffer.loadFromFile("../files/music/1.wav");
  treatPatientSound.setBuffer(treatPatientBuffer);
}

void MusicManager::PlayBackgroundGameMusic() {
  backgroundGameMusic.setVolume(10);
  backgroundGameMusic.setLoop(true);
  backgroundGameMusic.play();
}

void MusicManager::PlayBackgroundMenuMusic() {
  backgroundMenuMusic.setVolume(10);
  backgroundMenuMusic.setLoop(true);
  backgroundMenuMusic.play();
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

void MusicManager::PlayTransportSound() {
  isDrive = !isDrive;

  if (isDrive) {
    transportSound.setVolume(10);
    transportSound.setLoop(true);
    transportSound.play();
  } else {
    transportSound.stop();
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