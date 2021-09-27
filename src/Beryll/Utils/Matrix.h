#pragma once

#include "LibsHeaders.h"
#include "CppHeaders.h"

namespace Beryll
{
    //mat4 m;
    //m[1] = vec4(2.0); // sets the second column to all 2.0
    //m[0][0] = 1.0; // sets the upper left element to 1.0
    //m[2][3] = 2.0; // sets the 4th element of the third column to 2.0
    //m[1] refers to the SECOND COLUMN VECTOR
    //Remember, OpenGL defaults to column major matrices, which means access is of the format mat[col][row].
    //In the example, m[2][3] sets the 4th ROW (index 3) of the 3rd COLUMN (index 2) to 2.0.
    class Matrix
    {
    public:
        Matrix() = delete;

        static glm::mat4 aiToGlm(const aiMatrix4x4& aiMat)
        {
            glm::mat4 result{1.0f};
            result[0].x = aiMat.a1; result[1].x = aiMat.a2; result[2].x = aiMat.a3; result[3].x = aiMat.a4;
            result[0].y = aiMat.b1; result[1].y = aiMat.b2; result[2].y = aiMat.b3; result[3].y = aiMat.b4;
            result[0].z = aiMat.c1; result[1].z = aiMat.c2; result[2].z = aiMat.c3; result[3].z = aiMat.c4;
            result[0].w = aiMat.d1; result[1].w = aiMat.d2; result[2].w = aiMat.d3; result[3].w = aiMat.d4;

            return result;
        }

        //static void decomposeAI()

        static void decompose4x4Glm(const glm::mat4& matr, glm::vec3& scale, glm::quat& rotation, glm::vec3& translation)
        {
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(matr, scale, rotation, translation, skew, perspective);
        }

        static glm::vec3 getScaleFrom4x4Glm(const glm::mat4& matr)
        {
            glm::vec3 scale;
            glm::vec3 translation;
            glm::quat rotation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(matr, scale, rotation, translation, skew, perspective);

            return scale;
        }

        static glm::vec3 getPositionFrom4x4Glm(const glm::mat4& matr)
        {
            glm::vec3 scale;
            glm::vec3 translation;
            glm::quat rotation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(matr, scale, rotation, translation, skew, perspective);

            return translation;
        }

        static glm::quat getRotationFrom4x4Glm(const glm::mat4& matr)
        {
            glm::vec3 scale;
            glm::vec3 translation;
            glm::quat rotation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(matr, scale, rotation, translation, skew, perspective);

            return rotation;
        }
    };
}