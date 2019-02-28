#ifndef SRC_SOLVERS_MYSOLVER_H
#define SRC_SOLVERS_MYSOLVER_H

#include <bits/stdc++.h>
#include "../base.h"
#include "../domain.h"

class MySolver: public Solver {
  public:
    MySolver(InputReader& input, OutputWriter& output):
      Solver(input, output) {}

    void Solve() override {
      vector<Photo> photos = input_.GetPhotos();
      Photo odd_photo;
      bool has_odd_photo = false;
      for (Photo& photo : photos) {
        if (photo.horizontal) {
          output_.Add(photo);
          /* cerr << "Adaugat " << photo.id << endl; */
        }
      }
      for (Photo& photo : photos) {
        if (!photo.horizontal) {
          if (has_odd_photo) {
            output_.Add(odd_photo, photo);
            has_odd_photo = false;
          } else {
            odd_photo = photo;
            has_odd_photo = true;
          }
        }
      }
    }
};

#endif  // SRC_SOLVERS_MYSOLVER_H
