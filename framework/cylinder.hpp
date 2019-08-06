#ifndef Cylinder_HPP
#define Cylinder_HPP

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <math.h>

#include "hitpoint.hpp"
#include "ray.hpp"
#include "shape.hpp"

class Cylinder : public Shape{
    public:
        Cylinder();
        Cylinder(glm::vec3 p1, glm::vec3 p2, float radius);
        Cylinder(glm::vec3 p1, glm::vec3 p2, float radius, std::string name, std::shared_ptr<Material> mat);
        ~Cylinder();

        float area() const;
        float volume() const;

        std::ostream& print(std::ostream& os) const override;
        HitPoint intersect(Ray const&) override;

    private:
        glm::vec3 p1_;
        glm::vec3 p2_;
        float radius_;
};

std::ostream& operator<<(std::ostream& os, Cylinder const& t);


#endif