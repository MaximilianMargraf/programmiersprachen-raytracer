#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <math.h>

#include "hitpoint.hpp"
#include "ray.hpp"
#include "shape.hpp"

class Triangle : public Shape{
    public:
        Triangle();
        Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
        Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, std::string name, std::shared_ptr<Material> mat);
        ~Triangle();

        float area() const;
        float volume() const;

        std::ostream& print(std::ostream& os) const override;
        HitPoint intersect(Ray const&) override;
        void translate(glm::vec3 const&) override;
        void scale(float const&) override;

    private:
        glm::vec3 p1_;
        glm::vec3 p2_;
        glm::vec3 p3_;
};

std::ostream& operator<<(std::ostream& os, Triangle const& t);


#endif