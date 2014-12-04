class Array
  # Uses the first and second element in the Array to create a Chipmunk2d::Vect
  # @return [Chipmunk2d::Vect]
  def to_vect
    Chipmunk2d::Vect.new(self[0], self[1])
  end
end
