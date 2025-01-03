namespace core::interface {

class IObject {

public:
    virtual void update(float) = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
};

} // namespace core.interface