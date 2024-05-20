#include "Point.h"
#include <vector>

#include <string>

#include <algorithm>

#include <chrono>

#include <iomanip>

#include <iostream>



using namespace std;



static pair<Point, Point> PointsBruteForce(vector<Point>& points, size_t start, size_t end) {

    pair<Point, Point> closest = make_pair(points.at(start), points.at(start + 1));

    double min = points.at(start).distance(points.at(start + 1));



    for (size_t i = start; i <= end; ++i) {

        for (size_t j = i + 1; j < +end; ++j) {

            if (points.at(i).distance(points.at(j)) < min) {

                min = points.at(i).distance(points.at(j));

                closest = make_pair(points.at(i), points.at(j));

            }

        }

    }



    return closest;

}



template <typename T, typename Comparator>

void merge(vector<T>& v, vector<T>& tmp, size_t leftHalf, size_t rightHalf, size_t rightEndIndex, Comparator comp) {

    size_t leftEnd = rightHalf - 1;

    size_t tempPos = leftHalf;

    size_t numElemenets = rightEndIndex - leftHalf + 1;



    while (leftHalf <= leftEnd && rightHalf <= rightEndIndex) {

        if (comp(v[leftHalf], v[rightHalf]))

            tmp[tempPos++] = move(v[leftHalf++]);

        else

            tmp[tempPos++] = move(v[rightHalf++]);

    }



    while (leftHalf <= leftEnd)

        tmp[tempPos++] = move(v[leftHalf++]);



    while (rightHalf <= rightEndIndex)

        tmp[tempPos++] = move(v[rightHalf++]);



    for (size_t i = 0; i < numElemenets; ++i, --rightEndIndex)

        v[rightEndIndex] = move(tmp[rightEndIndex]);

}



template <typename T, typename Comparator>

void mergeSort(vector<T>& v, vector<T>& tmp, size_t left, size_t right, Comparator comp) {

    if (left < right) {

        size_t center = (left + right) / 2;

        mergeSort(v, tmp, left, center, comp);

        mergeSort(v, tmp, center + 1, right, comp);

        merge(v, tmp, left, center + 1, right, comp);

    }

}



template <typename T, typename Comparator>

void mergeSort(vector<T>& v, Comparator comp) {

    vector<T> tmp(v.size());



    if (v.size() < 1)

        throw invalid_argument("Vector is empty");



    mergeSort(v, tmp, 0, v.size() - 1, comp);

}



pair<Point, Point> findClosestPoints(vector<Point>& points, size_t start, size_t end) {



    if ((end - start) + 1 <= 4)

        return PointsBruteForce(points, start, end);



    size_t mid = (start + end) / 2;



    pair<Point, Point> minLeftHalf = findClosestPoints(points, start, mid);

    pair<Point, Point> minRightHalf = findClosestPoints(points, mid + 1, end);



    double midPoint = points.at(mid).getX();

    double leftHalfDistance = minLeftHalf.first.distance(minLeftHalf.second);

    double rightHalfDistance = minRightHalf.first.distance(minRightHalf.second);



    pair<Point, Point> closestPair;



    if (leftHalfDistance < rightHalfDistance)

        closestPair = minLeftHalf;

    else

        closestPair = minRightHalf;



    double upperBound = min(leftHalfDistance, rightHalfDistance);



    vector<Point> strip;

    copy_if(points.begin() + start, points.begin() + end - 1, back_inserter(strip), [midPoint, upperBound](Point p) {

        return abs(p.getX() - midPoint) < upperBound;

        });



    mergeSort(strip, Point::CompareYCoordinate());



    for (size_t i = 0; i < strip.size(); ++i) {

        for (size_t j = i + 1; j < strip.size() && (strip.at(j).getY() - strip.at(i).getY()) < upperBound; ++j) {

            if (strip.at(i).distance(strip.at(j)) < upperBound) {

                upperBound = strip.at(i).distance(strip.at(j));

                closestPair = make_pair(strip.at(i), strip.at(j));

            }

        }

    }



    return closestPair;

}



pair<Point, Point> findClosestPoints(vector<Point>& points) {

    mergeSort(points, Point::CompareXCoordinate());

    return findClosestPoints(points, 0, points.size() - 1);

}



int main() {

    string filename;

    cout << "Enter Filename: ";

    cin >> filename;

    ifstream input(filename);

    if (!input.is_open()) {

        cout << "File not found" << endl;

        return 0;

    }

    cin.ignore();



    vector<Point> points;

    double x, y;



    while (input >> x >> y)

        points.push_back(Point(x, y));



    if (points.size() < 2) {

        cout << "Bad file. Not enough points to calculate distance" << endl;

        return 0;

    }



    auto start = chrono::high_resolution_clock::now();



    pair<Point, Point> closestPair = findClosestPoints(points);



    auto end = chrono::high_resolution_clock::now();

    auto time = chrono::duration_cast<chrono::milliseconds>(end - start);



    cout << "Closest points are: (" << closestPair.first.getX() << ", " << closestPair.first.getY() << ")";

    cout << " and (" << closestPair.second.getX() << ", " << closestPair.second.getY() << ")";

    cout << " with distance " << closestPair.first.distance(closestPair.second) << "\n";



    cout << "Time: " << time.count() << "ms" << "\n";



}
