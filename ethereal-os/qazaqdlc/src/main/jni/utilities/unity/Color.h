struct Color {
    union
    {
        struct
        {
            float r, b, g, a;
        };
        float data[4];
    };

    Color() {
        SetColor(0, 0, 0, 255);
    }

    Color(float r, float g, float b) {
        SetColor(r, g, b, 255);
    }

    Color(float r, float g, float b, float a) {
        SetColor(r, g, b, a);
    }


  /*/  void SetColor(float r1, float g1, float b1, float a1 = 255) {
        r = r1;
        g = g1;
        b = b1;
        a = a1;
    }/*/
	
	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			_color[0] = (uint8_t)r;
			_color[1] = (uint8_t)g;
			_color[2] = (uint8_t)b;
			_color[3] = (uint8_t)a;
		}

		void GetColor(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const {
			r = _color[0];
			g = _color[1];
			b = _color[2];
			a = _color[3];
		}
		
		int rs() { return _color[0]; }
		int gs() { return _color[1]; }
		int bs() { return _color[2]; }
		int as() { return _color[3]; }

		int GetR() { return _color[0]; }
		int GetG() { return _color[1]; }
		int GetB() { return _color[2]; }
		int GetA() { return _color[3]; }

		void SetR(uint8_t _i) { _color[0] = _i; }
		void SetG(uint8_t _i) { _color[1] = _i; }
		void SetB(uint8_t _i) { _color[2] = _i; }
		void SetA(uint8_t _i) { _color[3] = _i; }

		
	uint8_t &operator[](int index) {
			return _color[index];
		}

		const uint8_t &operator[](int index) const {
			return _color[index];
		}

		bool operator == (const Color &rhs) const {
			return (*((int *)this) == *((int *)&rhs));
		}

		bool operator != (const Color &rhs) const {
			return !(operator==(rhs));
		}
		
		Color &operator=(const Color &rhs) {
			*(int*)(&_color[0]) = *(int*)&rhs._color[0];
			return *this;
		}

		Color operator+(const Color &rhs) const {
			int red = _color[0] + rhs._color[0];
			int green = _color[1] + rhs._color[1];
			int blue = _color[2] + rhs._color[2];
			int alpha = _color[3] + rhs._color[3];

			red = red > 255 ? 255 : red;
			green = green > 255 ? 255 : green;
			blue = blue > 255 ? 255 : blue;
			alpha = alpha > 255 ? 255 : alpha;

			return Color(red, green, blue, alpha);
		}

		Color operator-(const Color &rhs) const {
			int red = _color[0] - rhs._color[0];
			int green = _color[1] - rhs._color[1];
			int blue = _color[2] - rhs._color[2];
			int alpha = _color[3] - rhs._color[3];

			red = red < 0 ? 0 : red;
			green = green < 0 ? 0 : green;
			blue = blue < 0 ? 0 : blue;
			alpha = alpha < 0 ? 0 : alpha;
			return Color(red, green, blue, alpha);
		}

		operator const uint8_t*() {
			return (uint8_t*)(&_color[0]);
		}
	/*
	ImU32 GetU32()
{
return ((_color[3] & 0xff) << 24) + ((_color[2] & 0xff) << 16) + ((_color[1] & 0xff) << 8)
+ (_color[0] & 0xff);
//return (ImU32)(((_color[3] & 0xff) << 24) + ((_color[0] & 0xff) << 16) + ((_color[1] & 0xff) << 8) + (_color[2] & 0xff));
}*/

static Color FromHSB(float hue, float saturation, float brightness)
{
float h = hue == 1.0f ? 0 : hue * 6.0f;
float f = h - (int)h;
float p = brightness * (1.0f - saturation);
float q = brightness * (1.0f - saturation * f);
float t = brightness * (1.0f - (saturation * (1.0f - f)));
if (h < 1)
{
return Color(
(unsigned char)(brightness * 255),
(unsigned char)(t * 255),
(unsigned char)(p * 255)
);
}
else if (h < 2)
{
return Color(
(unsigned char)(q * 255),
(unsigned char)(brightness * 255),
(unsigned char)(p * 255)
);
}
else if (h < 3)
{
return Color(
(unsigned char)(p * 255),
(unsigned char)(brightness * 255),
(unsigned char)(t * 255)
);
}
else if (h < 4)
{
return Color(
(unsigned char)(p * 255),
(unsigned char)(q * 255),
(unsigned char)(brightness * 255)
);
}
else if (h < 5)
{
return Color(
(unsigned char)(t * 255),
(unsigned char)(p * 255),
(unsigned char)(brightness * 255)
);
}
else
{
return Color(
(unsigned char)(brightness * 255),
(unsigned char)(p * 255),
(unsigned char)(q * 255)
);
}
}
private:
		uint8_t _color[4];
	};
    static Color Black(float a = 255) { return Color(0, 0, 0, a); }

    static Color Red(float a = 255) { return Color(255, 0, 0, a); }

    static Color Green(float a = 255) { return Color(0, 255, 0, a); }

    static Color Blue(float a = 255) { return Color(0, 0, 255, a); }

    static Color White(float a = 255) { return Color(255, 255, 255, a); }

    static Color Orange(float a = 255) { return Color(255, 153, 0, a); }

    static Color Yellow(float a = 255) { return Color(255, 255, 0, a); }

    static Color Cyan(float a = 255) { return Color(0, 255, 255, a); }

    static Color Magenta(float a = 255) { return Color(255, 0, 255, a); }

    static Color random(float a = 255) {
        float r = static_cast <float> (rand()) / static_cast <float> (255);
        float g = static_cast <float> (rand()) / static_cast <float> (255);
        float b = static_cast <float> (rand()) / static_cast <float> (255);
        return Color(r, g, b, a);
    };
	class Rainbow
	{
	public:
		float r, g, b, a;
		Rainbow(float r, float g, float b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = 255;
		}
	};
