#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include <cstdint>

class PerlinNoise
{
public:
    float GetNoise(float x, float y);

    float GetNoise(float x, float y, float z);

    void SetOctave(int octave);
    void SetFrequency(float frequency);
    void SetAmplitude(float apmlitude);
    void SetLacunarity(float lacunarity);
    void SetPersistence(float persistence);

private:
    int   m_Octave         = 3;
    float m_Frequency      = 1.0f;
	float m_Amplitude      = 1.0f;
	float m_Lacunarity     = 2.0f;
	float m_Persistence    = 0.5f;

    static uint8_t s_Perm[512];

private:
    float Perlin(float x, float y);

    float Perlin(float x, float y, float z);

    float FastFloor(float f);

    float Fade(float t);

    float Lerp(float a, float b, float t);

    float Grad(int hash, float x, float y);
    
    float Grad(int hash, float x, float y, float z);    
}

#endif // !PERLINNOISE_HPP
