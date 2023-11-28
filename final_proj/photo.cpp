class photo {
  private: 
    int pin;
    int physical_angle;
    int logical_angle;

  public: 
    photo(int pin, int physical_angle, int logical_angle) {
      this->pin = pin;
      this->physical_angle = physical_angle;
      this->logical_angle = logical_angle;
    }
};