#ifndef SRC_BASE_H
#define SRC_BASE_H

#include <bits/stdc++.h>
#include "domain.h"

using namespace std;

class InputReader {
  public:
    void Read() {
      int num_photos;
      cin >> num_photos;
      for (int i = 0; i < num_photos; ++i) {
        /* fprintf(stderr, "Incep sa citesc poza %d\n", i); */
        Photo photo;
        string orientation;
        int num_tags;
        cin >> orientation >> num_tags;
        vector<string> tags;
        for (int j = 0; j < num_tags; ++j) {
          string tag;
          cin >> tag;
          tags.push_back(tag);
        }
        photo.tags = tags;
        photo.horizontal = (orientation[0] == 'H');
        photo.id = i;
        photos_.push_back(photo);
        /* fprintf(stderr, "Citit poza %d\n", i); */
      }
    }

    vector<Photo> GetPhotos() const {
      return photos_;
    }

  protected:
    vector<Photo> photos_;
};


class OutputWriter {
  public:
    /* void Assign(int photo_id, int slide_id) { */
    /*   assert(false); */
    /* } */

    void Add(Photo photo) {
      Slide slide(photo);
      slides_.push_back(slide);
    }

    void Add(Photo photo_1, Photo photo_2) {
      Slide slide(photo_1, photo_2);
      slides_.push_back(slide);
    }

    void Write() {
      DequeOptimization();
      cout << slides_.size() << endl;
      for (Slide& slide : slides_) {
        for (Photo& photo : slide.photos) {
          cout << photo.id << ' ';
        }
        cout << endl;
      }
    }

    int NumSlides() {
      return slides_.size();
    }

  protected:
    void DequeOptimization() {
      fprintf(stderr, "Prima poza INAINTE DE deque optimization: %d\n",
              slides_[0].photos[0].id);

      vector<int> partial_sums;
      partial_sums.push_back(0);
      int total_sum = 0;
      Slide last_slide;

      int best_score = -1;
      int best_beginning = 0;
      for (int i = 0; i < 2 * slides_.size(); ++i) {
        total_sum += GetScoreBetweenSlides(last_slide, slides_[i % slides_.size()]);
        partial_sums.push_back(total_sum);
        last_slide = slides_[i % slides_.size()];

        if (i >= slides_.size()
            && partial_sums[i] - partial_sums[i - slides_.size()] > best_score) {
          best_score = partial_sums[i] - partial_sums[i - slides_.size()];
          best_beginning = i - slides_.size();
        }
      }

      vector<Slide> slides;
      slides.insert(slides.end(), slides_.begin() + best_beginning, slides_.end());
      slides.insert(slides.end(), slides_.begin(), slides_.begin() + best_beginning);
      slides_ = slides;

      fprintf(stderr, "Prima poza DUPA deque optimization: %d\n",
              slides_[0].photos[0].id);
    }

    vector<Slide> slides_;
};


class Solver {
  public:
    Solver(InputReader& input, OutputWriter& output):
      input_(input), output_(output) {
    }

    virtual ~Solver() {}

    virtual void Solve() {}

  protected:
    InputReader& input_;
    OutputWriter& output_;
};

#endif  // SRC_BASE_H
