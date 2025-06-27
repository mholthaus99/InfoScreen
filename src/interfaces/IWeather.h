class IWeather {
public:
     virtual const char* getCurrentConditions() = 0;
     virtual void update() = 0;
     virtual ~IWeather() {}
};
     