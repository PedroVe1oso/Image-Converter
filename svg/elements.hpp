//! @file elements.hpp
#ifndef __svg_elements_hpp__
#define __svg_elements_hpp__

#include "shape.hpp"

namespace svg {
    class ellipse : public shape {
    protected:
        point center;
        point radius;
    public:
        ellipse(const svg::color &fill, const point &center, const point &radius);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int v) override;
        shape *duplicate() const override;
    };

    class circle final : public ellipse {
    public:
        circle(const svg::color &fill, const point &center, const point &radius);
    };


    class polygon : public shape {
    protected:
        std::vector<point> points;
    public:
        polygon(const svg::color &fill, const std::vector<point> &points);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int v) override;
        shape *duplicate() const override;
    };

    class rect final : public polygon {
    public:
        rect(const svg::color &fill, const point upperLeft, const int width, const int height);
    };


    class polyline : public shape {
    protected:
        std::vector<point> points;
    public:
        polyline(const svg::color &stroke, const std::vector<point> &points);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int v) override;
        shape *duplicate() const override;
    };

    class line final : public polyline {
    public:
        line(const svg::color &stroke, const point p1, const point p2);
    };
}
#endif
