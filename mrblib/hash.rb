class Hash
  # Uses keys, :x and :y to create a new Chipmunk2d::Vect
  #
  # @return [Chipmunk2d::Vect]
  def to_vect
    Chipmunk2d::Vect.new(fetch(:x), fetch(:y))
  end
end
