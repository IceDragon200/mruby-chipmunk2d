module Chipmunk2d
  class Arbiter
    # @return [Float]
    def restitution
    end

    # @param [Float] res
    # @return [void]
    def restitution=(res)
    end

    # @return [Float]
    def friction
    end

    # @param [Float] fri
    # @return [void]
    def friction=(fri)
    end

    # @return [Vect]
    def surface_velocity
    end

    # @param [Vect] velo
    # @return [void]
    def surface_velocity=(velo)
    end

    # @return [Vect]
    def total_impulse
    end

    # @return [Float]
    def total_ke
    end

    # @return [Boolean]
    def ignore
    end

    # @return [Array<Shape>]
    def shapes
    end

    # @return [Array<Body>]
    def bodies
    end

    # @return [ContactPointSet]
    def contact_point_set
    end

    # @param [ContactPointSet] cps
    # @return [void]
    def contact_point_set=(cps)
    end

    # @return [Boolean]
    def first_contact?
    end

    # @return [Boolean]
    def removal?
    end

    # @return [Vect]
    def normal
    end

    # @param [Integer] index
    # @return [Vect]
    def point_a(index)
    end

    # @param [Integer] index
    # @return [Vect]
    def point_b(index)
    end

    # @param [Integer] index
    # @return [Float]
    def depth(index)
    end

    # @param [Space] space
    # @return [Boolean]
    def call_wildcard_begin_a(space)
    end

    # @param [Space] space
    # @return [Boolean]
    def call_wildcard_begin_b(space)
    end

    # @param [Space] space
    # @return [Boolean]
    def call_wildcard_pre_solve_a(space)
    end

    # @param [Space] space
    # @return [Boolean]
    def call_wildcard_pre_solve_b(space)
    end

    # @param [Space] space
    # @return [void]
    def call_wildcard_post_solve_a(space)
    end

    # @param [Space] space
    # @return [void]
    def call_wildcard_post_solve_b(space)
    end

    # @param [Space] space
    # @return [Boolean]
    def call_wildcard_separate_a(space)
    end

    # @param [Space] space
    # @return [Boolean]
    def call_wildcard_separate_b(space)
    end
  end
end
