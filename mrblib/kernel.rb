module Kernel
  # Shorthand method for creating Vects
  # @param [Float] x
  # @param [Float] y
  # @return [Chipmunk2d::Vect]
  def vec2(x, y)
    Chipmunk2d::Vect.new(x, y)
  end
end
