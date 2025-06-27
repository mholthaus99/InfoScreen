class ISensor {
public:
     virtual float getValue() = 0;
     virtual void update() = 0;
     virtual ~ISensor() {}
};
     