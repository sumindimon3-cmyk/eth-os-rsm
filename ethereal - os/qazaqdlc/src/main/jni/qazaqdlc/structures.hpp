struct bools {
    bool isGUIopened = true;
    bool inited = false;
    bool snowflakes = true;
	
    bool silentAim = false;
	bool silentFOV = false;
	bool silentVisibleCheck = false;
    
    bool ESP = false;
    bool BoxESP = false;
    bool TracerESP = false;
    bool HealthESP = false;
	bool ArmorESP = false;
	bool DistanceESP = false;
} bools;

struct ints {
    int glWidth, glHeight;
    int tab = 1;
	int backgroundTransparency = 70;
	int line_position = 0;
	
	int hitMode = 0;
	int headHitChance = 100;
    int neckHitChance = 0;
    int hipHitChance = 0;
    int selectedBone = 0;
    int silentSelected = 0;
	int silentType = 0;
} ints;

struct floats {
	float dpiScale = 1.1f;
	float GUIalpha = 0.0f;
	float GUIscale = 0.8f;
	float animationSpeed = 5.0f;
	
    float silentAimFOV = 30.0f;
    
    float spamSpeed = 12.5f;  
} floats;

namespace chars {
    static char customMessage[256] = "";
    
	std::string Up = oxorany("Up");
	std::string Middle = oxorany("Middle");
	std::string Down = oxorany("Down");
	
	const char* line_position[] = {
		Up.c_str(),
		Middle.c_str(),
		Down.c_str()
	};
	
	std::string Circle = oxorany("Circle");
	std::string Hexagon = oxorany("Hexagon");
	std::string Pentagon = oxorany("Pentagon");
	std::string Triangle = oxorany("Triangle");
	std::string BrokenTriangle = oxorany("Broken Triangle");
	
	const char* silentShapes[] = {
		Circle.c_str(),
		Hexagon.c_str(),
		Pentagon.c_str(),
		Triangle.c_str(),
		BrokenTriangle.c_str()
	};
	
	std::string Bone = oxorany("Bone");
	std::string Hitchance = oxorany("Hit chance");
	
	const char* silentTypes[] = {
		Bone.c_str(),
		Hitchance.c_str()
	};
	
	std::string Head = oxorany("Head");
	std::string Neck = oxorany("Neck");
	std::string Hip = oxorany("Hip");
	
	const char* silentSelectedBone[] = {
		Head.c_str(),
		Neck.c_str(),
		Hip.c_str()
	};
	
}

namespace colors {
	static ImVec4 textColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	static ImVec4 silentColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}

enum HitMode {
    BoneBased = 0,  
    ChanceBased = 1 
};
