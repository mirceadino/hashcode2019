#ifndef SRC_SOLVERS_HORIZONTAL_GREEDY_SOLVER_H
#define SRC_SOLVERS_HORIZONTAL_GREEDY_SOLVER_H

#include <bits/stdc++.h>
#include "../base.h"
#include "../domain.h"

class HorizontalGreedySolver: public Solver {
  public:
    HorizontalGreedySolver(InputReader& input, OutputWriter& output):
      Solver(input, output) {}

    void AddVerticalPairs() {
      vector<Photo> photos = input_.GetPhotos();
      Photo odd_photo;
      bool has_odd_photo = false;
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

    void Solve() override {
      vector<Photo> photos = input_.GetPhotos();

      // Create id to photo.
      map<int, Photo> id_to_photo;
      for (Photo& photo : photos) {
        id_to_photo[photo.id] = photo;
      }

      // Create tag to photos.
      map<string, vector<int>> tag_to_photos;
      for (Photo& photo : photos) {
        if (!photo.horizontal) {
          continue;
        }

        for (string& tag : photo.tags) {
          tag_to_photos[tag].push_back(photo.id);
        }
      }

      bitset<100000> visited_photos = 0;

      do {
        bool not_found = true;
        Photo last_photo;
        for (Photo& photo : photos) {
          if (!visited_photos[photo.id] && photo.horizontal) {
            last_photo = photo;
            not_found = false;
            break;
          }
        }

        if (not_found) {
          break;
        }

        output_.Add(last_photo);
        visited_photos[last_photo.id] = true;

        do {
          // Get photo candidate ids.
          unordered_set<int> candidate_ids;
          for (string& tag : last_photo.tags) {
            for (int& id : tag_to_photos[tag]) {
              if (!visited_photos[id]) {
                candidate_ids.insert(id);
                if (candidate_ids.size() >= 100) {
                  break;
                }
              }
            }
            if (candidate_ids.size() >= 100) {
              break;
            }
          }

          // Break condition == if no photo candidates.
          if (candidate_ids.empty()) {
            break;
          }

          // Find best candidate.
          int best_score = -1;
          int best_candidate_id = -1;
          for (const int& id : candidate_ids) {
            int score = GetScoreBetweenSlides(Slide(id_to_photo[id]), Slide(last_photo));
            if (score > best_score) {
              best_score = score;
              best_candidate_id = id;
            }
          }

          last_photo = id_to_photo[best_candidate_id];
          output_.Add(last_photo);
          visited_photos[last_photo.id] = true;
        } while (true);
      } while (true);

      AddVerticalPairs();
    }
};

#endif  // SRC_SOLVERS_HORIZONTAL_GREEDY_SOLVER_H
