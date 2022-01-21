#include <cassert>
#include "elements.hpp"

namespace svg {
    ellipse::ellipse(const svg::color &fill,
                     const point &center,
                     const point &radius) :
            shape(fill), center(center), radius(radius) {

    }
    void ellipse::draw(png_image &img) const {
        img.draw_ellipse(center, radius, get_color());
    }
    void ellipse::translate(const point &t) {
        center = center.translate(t);
    }
    void ellipse::scale(const point &origin, int v) {
        radius.x *= v;
        radius.y *= v;
        center = center.scale(origin,v);
    }
    void ellipse::rotate(const point &origin, int degrees) {
        center = center.rotate(origin, degrees);
    }
    shape *ellipse::duplicate() const {
        return new ellipse(get_color(), center, radius);
    }

    circle::circle(const svg::color &fill,
                   const point &center,
                   const point &radius) :
                   ellipse(fill, center, radius) {

    }

    polygon::polygon(const svg::color &fill, const std::vector<point>& points) :
            shape(fill), points(points) {

    }
    void polygon::draw(png_image &img) const {
        img.draw_polygon(points,get_color());
    }
    void polygon::translate(const point &t) {
        for(point& point : points){
            point = point.translate(t);
        }
    }
    void polygon::scale(const point &origin, int v) {
        for(point& point : points){
            point.x *= v;
            point.y *= v;
        }
    }
    void polygon::rotate(const point &origin, int v) {

    }
    shape *polygon::duplicate() const {
        return new polygon(get_color(), points);
    }

    rect::rect(const svg::color &fill, const point upperLeft, const int width, const int height) :
            polygon(fill, {upperLeft,
                           {upperLeft.x, upperLeft.y + height - 1},
                           {upperLeft.x + width - 1, upperLeft.y + height - 1},
                           {upperLeft.x + width - 1, upperLeft.y}}){

    }

    polyline::polyline(const svg::color &stroke, const std::vector<point>& points) :
            shape(stroke), points(points){

    }
    void polyline::draw(png_image &img) const {
        for (auto it = points.begin(); it != points.end(); it++){
            img.draw_line(*it, *std::next(it), get_color());
            if(std::next(std::next(it)) == points.end()) break;
        }
    }
    void polyline::translate(const point &t) {
        for(point& point : points){
            point = point.translate(t);
        }
    }
    void polyline::scale(const point &origin, int v) {
        for(point& point : points){
            point.x *= v;
            point.y *= v;
        }
    }
    void polyline::rotate(const point &origin, int v) {

    }
    shape *polyline::duplicate() const {
        return new polyline(get_color(), points);
    }

    line::line(const svg::color &stroke, const point point1, const point point2) :
            polyline(stroke, {point1, point2}){

    }
}
