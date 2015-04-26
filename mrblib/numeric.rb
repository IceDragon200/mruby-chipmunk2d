class Numeric
  # Creates a new Chipmunk2d::Vect using self as x, y
  #
  # @return [Chipmunk2d::Vect]
  def to_vect
    Chipmunk2d::Vect.new(self, self)
  end
end
