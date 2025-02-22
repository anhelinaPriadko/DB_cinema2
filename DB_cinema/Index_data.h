#pragma once

struct IndexHallType {
    int id;
    long position;

    IndexHallType(int id = 0, long pos = -1)
        : id(id), position(pos) {
    }
};

struct IndexHall {
    int id;
    long position;
    int type_id;

    IndexHall(int id = 0, long pos = -1, int t_id = 0)
        : id(id), position(pos), type_id(t_id) {
    }
};
