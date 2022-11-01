#include "PerlinNoise.hpp"

float PerlinNoise::GetNoise(float x, float y)
{
    float result = 0.0f;
	float frequency = m_Frequency;
	float amplitude = m_Amplitude;

	for (int i = 0; i < m_Octave; i++)
	{
		result += Perlin(x * frequency, y * frequency) * amplitude;
		frequency *= m_Lacunarity;
		amplitude *= m_Persistence;
	}

	return result;
}
    

float PerlinNoise::GetNoise(float x, float y, float z)
{
    float result = 0.0f;
	float frequency = m_Frequency;
	float amplitude = m_Amplitude;

	for (int i = 0; i < m_Octave; i++)
	{
		result += Perlin(x * frequency, y * frequency, z * frequency) * amplitude;
		frequency *= m_Lacunarity;
		amplitude *= m_Persistence;
	}

	return result;
}

void PerlinNoise::SetOctave(int octave)
{
    m_Octave = octave;
}

void PerlinNoise::SetFrequency(float frequency)
{
    m_Frequency = frequency;
}

void PerlinNoise::SetAmplitude(float apmlitude)
{
    m_Amplitude = apmlitude;
}

void PerlinNoise::SetLacunarity(float lacunarity)
{
    m_Lacunarity = lacunarity;
}

void PerlinNoise::SetPersistence(float persistence)
{
    m_Persistence = persistence;
}

uint8_t PerlinNoise::s_Perm[512]
{
	151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
	151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

float PerlinNoise::Perlin(float x, float y)
{
    int xi = FastFloor(x);
	int yi = FastFloor(y);
	x -= (float)xi;
	y -= (float)yi;
	xi &= 255;
	yi &= 255;

	float u = Fade(x);
	float v = Fade(y);

	int aa = s_Perm[s_Perm[xi] + yi];
	int ab = s_Perm[s_Perm[xi] + yi + 1];
	int ba = s_Perm[s_Perm[xi + 1] + yi];
	int bb = s_Perm[s_Perm[xi + 1] + yi + 1];

	return Lerp(
		Lerp(Grad(aa, x, y), Grad(ba, x - 1.0f, y), u),
		Lerp(Grad(ab, x, y - 1.0f), Grad(bb, x - 1.0f, y - 1.0f), u), v);
}

float  PerlinNoise::Perlin(float x, float y, float z)
{
    int xi = FastFloor(x);
	int yi = FastFloor(y);
	int zi = FastFloor(z);
	x -= (float)xi;
	y -= (float)yi;
	z -= (float)zi;
	xi &= 255;
	yi &= 255;
	zi &= 255;

	float u = Fade(x);
	float v = Fade(y);
	float n = Fade(z);

	int aaa = s_Perm[s_Perm[s_Perm[xi] + yi] + zi];
	int aba = s_Perm[s_Perm[s_Perm[xi] + yi + 1] + zi];
	int aab = s_Perm[s_Perm[s_Perm[xi] + yi] + zi + 1];
	int abb = s_Perm[s_Perm[s_Perm[xi] + yi + 1] + zi + 1];
	int baa = s_Perm[s_Perm[s_Perm[xi + 1] + yi] + zi];
	int bba = s_Perm[s_Perm[s_Perm[xi + 1] + yi + 1] + zi];
	int bab = s_Perm[s_Perm[s_Perm[xi + 1] + yi] + zi + 1];
	int bbb = s_Perm[s_Perm[s_Perm[xi + 1] + yi + 1] + zi + 1];

	return Lerp(
		Lerp(
			Lerp(Grad(aaa, x, y, z), Grad(baa, x - 1.0f, y, z), u),
			Lerp(Grad(aba, x, y - 1.0f, z), Grad(bba, x - 1.0f, y - 1.0f, z), u), v),
		Lerp(
			Lerp(Grad(aab, x, y, z - 1.0f), Grad(bab, x - 1.0f, y, z - 1.0f), u),
			Lerp(Grad(abb, x, y - 1.0f, z - 1.0f), Grad(bbb, x - 1.0f, y - 1.0f, z - 1.0f), u), v), n);
}

float PerlinNoise::FastFloor(float f)
{
	return (f > 0.0f) ? (int)f : (int)f - 1;
}

float PerlinNoise::Fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::Lerp(float a, float b, float t)
{
	return (1 - t) * a + t * b;
}

float PerlinNoise::Grad(int hash, float x, float y)
{
	return ((hash & 0b10) ? x : -x) + ((hash & 0b01) ? y : -y);
}

float PerlinNoise::Grad(int hash, float x, float y, float z)
{
	return ((hash & 0b100) ? x : -x) + ((hash & 0b010) ? y : -y) + (((hash & 0b001) ? y : -y));
}
