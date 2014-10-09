module Chipmunk2d
  class Body
    def self.new_kinematic
      body = new(0.0, 0.0)
      body.type = TYPE_KINEMATIC
      body
    end

    def self.new_static
      body = new(0.0, 0.0)
      body.type = TYPE_STATIC
      body
    end
  end
end
