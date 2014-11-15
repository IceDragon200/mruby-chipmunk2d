module Kernel
  # Shorthand method for creating Vects
  # @param [Float] x
  # @param [Float] y
  # @return [Chipmunk2d::Vect]
  def vec2(x, y)
    Chipmunk2d::Vect.new(x, y)
  end
end

module Chipmunk2d
  class Vect
    # @return [Array<Float>]
    def to_a
      return x, y
    end

    # @return [String]
    def inspect
      # format isn't apart of the core mruby implementation, so I'll just
      # leave the id unconverted
      "<#{self.class}:#{__id__} x=#{x} y=#{y}>"
    end

    # @param [Chipmunk2d::Vect] other
    # @return [Boolean]
    def fuzzy_eql?(other)
      # shamelessy copied from mruby/test/assert.rb#check_float
      tolerance = 1e-12
      a, b = self.x, other.x
      if a.finite? && b.finite?
        return false unless (a - b).abs < tolerance
      end
      a, b = self.y, other.y
      if a.finite? && b.finite?
        return false unless (a - b).abs < tolerance
      end
      true
    end
  end
end
