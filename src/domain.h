#ifndef SRC_DOMAIN_H
#define SRC_DOMAIN_H

#include <bits/stdc++.h>

using namespace std;

struct Photo {
  vector<string> tags;
  bool horizontal;
  int id;
};

vector<string> UniteTags(vector<string> tags_1, vector<string> tags_2) {
  sort(tags_1.begin(), tags_1.end());
  sort(tags_2.begin(), tags_2.end());
  vector<string> tags(tags_1.size() + tags_2.size());
  auto it = set_union(tags_1.begin(), tags_1.end(), tags_2.begin(), tags_2.end(),
                      tags.begin());
  tags.resize(it - tags.begin());
  return tags;
}

struct Slide {
  vector<string> tags;
  vector<Photo> photos;

  Slide() {}

  Slide(Photo photo) {
    photos = {photo};
    tags = UniteTags(photo.tags, {});
  }

  Slide(Photo photo_1, Photo photo_2) {
    photos = {photo_1, photo_2};
    tags = UniteTags(photo_1.tags, photo_2.tags);
  }
};

int GetScoreBetweenSlides(Slide a, Slide b) {
  vector<string> diff;

  diff.clear();
  set_difference(a.tags.begin(), a.tags.end(), b.tags.begin(), b.tags.end(),
                 inserter(diff, diff.begin()));
  int score_0 = diff.size();

  diff.clear();
  set_difference(a.tags.begin(), a.tags.end(), b.tags.begin(), b.tags.end(),
                 inserter(diff, diff.begin()));
  int score_1 = diff.size();

  diff.clear();
  set_intersection(a.tags.begin(), a.tags.end(), b.tags.begin(), b.tags.end(),
                   inserter(diff, diff.begin()));
  int score_2 = diff.size();

  return min(score_0, min(score_1, score_2));
}

struct Slideshow {
  vector<Slide> slides;
};

#endif  // SRC_DOMAIN_H
