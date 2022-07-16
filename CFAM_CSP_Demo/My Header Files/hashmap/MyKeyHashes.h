#pragma once

struct My10PrecentageKeyHash {
    unsigned long operator()(const int& k) const
    {
        return k % 10;
    }
};

struct MyDoNothingKey {
    unsigned long operator()(const int& k) const {
        return k;
    }
};

struct MyMSISDNKey {
    unsigned long operator()(const int& k) const {
        return k % 10000000;
    }
};