#pragma once

class Node {
public:
    Node(int id);
    int getId() const;
    double getVoltage() const;
    void setVoltage(double v);
    bool isFixed() const;
    void setFixed(bool fixed);

private:
    int id;
    double voltage;
    bool fixed;
};
