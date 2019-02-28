#ifndef SRC_SOLVERS_SLIDE_SOLVER_H
#define SRC_SOLVERS_SLIDE_SOLVER_H

#include <bits/stdc++.h>
#include "../base.h"
#include "../domain.h"

class SlideSolver: public Solver {
  public:
    SlideSolver(InputReader& input, OutputWriter& output):
      Solver(input, output) {}

    void AddVerticalPairs() {
      vector<Photo> photos = input_.GetPhotos();
      Photo odd_photo;
      bool has_odd_photo = false;
      for (Photo& photo : photos) {
        if (!photo.horizontal && !visited_photos[photo.id]) {
          assert(false);
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
        for (string& tag : photo.tags) {
          tag_to_photos[tag].push_back(photo.id);
        }
      }

      visited_photos = 0;

      do {
        Slide last_slide;
        bool not_found = true;
        Photo last_photo;
        for (Photo& photo : photos) {
          if (!visited_photos[photo.id] && photo.horizontal) {
            last_photo = photo;
            not_found = false;
            break;
          }
        }

        if (!not_found) {
          output_.Add(last_photo);
          visited_photos[last_photo.id] = true;

          last_slide = Slide(last_photo);
        } else {
          Photo first_vertical;
          Photo second_vertical;
          bool has_odd_photo = false;
          not_found = true;
          for (Photo& photo : photos) {
            if (!photo.horizontal && !visited_photos[photo.id]) {
              if (has_odd_photo) {
                second_vertical = photo;
                not_found = false;
                break;
              } else {
                first_vertical = photo;
                has_odd_photo = true;
              }
            }
          }
          if (!not_found) {
            output_.Add(first_vertical, second_vertical);
            visited_photos[first_vertical.id] = true;
            visited_photos[second_vertical.id] = true;

            last_slide = Slide(first_vertical, second_vertical);
          } else {
            break;
          }
        }

        do {
          Slide best_horizontal_slide;
          Slide best_vertical_slide;

          // CHESTIA CU ORIZONTALE.
          {
            // Get photo candidate ids.
            unordered_set<int> candidate_ids;
            for (string& tag : last_slide.tags) {
              for (int& id : tag_to_photos[tag]) {
                if (!visited_photos[id] && id_to_photo[id].horizontal) {
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
              int score = GetScoreBetweenSlides(Slide(id_to_photo[id]), last_slide);
              if (score > best_score) {
                best_score = score;
                best_candidate_id = id;
              }
            }

            best_horizontal_slide = Slide(id_to_photo[best_candidate_id]);
          }

          // CHESTIA CU VERTICALE
          {
            // Get photo candidate ids.
            unordered_set<int> candidate_ids;
            for (string& tag : last_slide.tags) {
              for (int& id : tag_to_photos[tag]) {
                if (!visited_photos[id] && !id_to_photo[id].horizontal) {
                  candidate_ids.insert(id);
                  if (candidate_ids.size() >= 20) {
                    break;
                  }
                }
              }
              if (candidate_ids.size() >= 20) {
                break;
              }
            }

            // Break condition == if no photo candidates.
            if (candidate_ids.size() <= 1) {
              break;
            }

            // Find best candidate #1.
            int best_score = -1;
            int best_candidate_id = -1;
            for (const int& id : candidate_ids) {
              int score = GetScoreBetweenSlides(Slide(id_to_photo[id]), last_slide);
              if (score > best_score) {
                best_score = score;
                best_candidate_id = id;
              }
            }

            Photo first_vertical = id_to_photo[best_candidate_id];

            // Find best candidate #2.
            best_score = -1;
            best_candidate_id = -1;
            for (const int& id : candidate_ids) {
              if (id == first_vertical.id) {
                continue;
              }

              int score = GetScoreBetweenSlides(Slide(id_to_photo[id], first_vertical),
                                                last_slide);
              if (score > best_score) {
                best_score = score;
                best_candidate_id = id;
              }
            }

            // NOTE: De inlocuit candidate #2 cu un non-candidate vertical random.

            assert(best_candidate_id >= 0);
            Photo second_vertical = id_to_photo[best_candidate_id];
            best_vertical_slide = Slide(first_vertical, second_vertical);
          }

          if (GetScoreBetweenSlides(last_slide,
                                    best_horizontal_slide) > GetScoreBetweenSlides(last_slide,
                                        best_vertical_slide)) {
            last_slide = best_horizontal_slide;
            output_.Add(last_slide.photos[0]);
            visited_photos[last_slide.photos[0].id] = true;
          } else {
            last_slide = best_vertical_slide;
            output_.Add(last_slide.photos[0], last_slide.photos[1]);
            visited_photos[last_slide.photos[0].id] = true;
            visited_photos[last_slide.photos[1].id] = true;
          }
        } while (true);
      } while (true);

      AddVerticalPairs();
    }

  protected:
    bitset<100000> visited_photos;

};

#endif  // SRC_SOLVERS_SLIDE_SOLVER_H
