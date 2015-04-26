module Chipmunk2d
  class Space
    # Shorthand method for add_body, add_constraint or add_shape
    #
    # @param [Body, Constraint, Shape] obj
    def add(obj)
      case obj
      when Body       then add_body(obj)
      when Constraint then add_constraint(obj)
      when Shape      then add_shape(obj)
      else
        raise TypeError, "expected #{Body}, #{Constraint} or #{Shape}"
      end
    end

    # Shorthand method for remove_body, remove_constraint or remove_shape
    #
    # @param [Body, Constraint, Shape] obj
    def remove(obj)
      case obj
      when Body       then remove_body(obj)
      when Constraint then remove_constraint(obj)
      when Shape      then remove_shape(obj)
      else
        raise TypeError, "expected #{Body}, #{Constraint} or #{Shape}"
      end
    end
  end
end
