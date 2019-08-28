#ifndef Cone_HPP
#define Cone_HPP

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <math.h>

#include "hitpoint.hpp"
#include "ray.hpp"
#include "shape.hpp"

class Cone : public Shape{
    public:
        Cone();
        Cone(glm::vec3 p1, glm::vec3 p2, float radius);
        Cone(glm::vec3 p1, glm::vec3 p2, float radius, std::string name, std::shared_ptr<Material> mat);
        ~Cone();

        float area() const;
        float volume() const;

        std::ostream& print(std::ostream& os) const override;
        HitPoint intersect(Ray const&) override;
        void translate(glm::vec3 const&) override;
        void scale(float const&) override;

    private:
        glm::vec3 p1_;
        glm::vec3 p2_;
        float radius_;
};

std::ostream& operator<<(std::ostream& os, Cone const& t);


#endif