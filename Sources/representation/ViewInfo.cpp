#include "ViewInfo.h"

#include "core/StreamWrapper.h"

std::ostream& operator<<(std::stringstream& file, ViewInfo& view_info)
{
    WrapWriteMessage(file, view_info.base_frameset_);
    file << " ";

    file << view_info.underlays_.size();
    file << " ";
    for (auto it = view_info.underlays_.begin(); it != view_info.underlays_.end(); ++it)
    {
            WrapWriteMessage(file, *it);
            file << " ";
    }

    file << view_info.overlays_.size();
    file << " ";
    for (auto it = view_info.overlays_.begin(); it != view_info.overlays_.end(); ++it)
    {
            WrapWriteMessage(file, *it);
            file << " ";
    }

    file << view_info.angle_ << " ";

    return file;
}
std::istream& operator>>(std::stringstream& file, ViewInfo& view_info)
{
    WrapReadMessage(file, view_info.base_frameset_);

    size_t u_size;
    file >> u_size;
    view_info.underlays_.resize(u_size);
    for (size_t i = 0; i < u_size; ++i)
    {
        ViewInfo::FramesetInfo f;
        WrapReadMessage(file, f);
        view_info.underlays_[i] = f;
    }

    size_t o_size;
    file >> o_size;
    view_info.overlays_.resize(o_size);
    for (size_t i = 0; i < o_size; ++i)
    {
        ViewInfo::FramesetInfo f;
        WrapReadMessage(file, f);
        view_info.overlays_[i] = f;
    }

    file >> view_info.angle_;

    return file;
}

std::ostream& operator<<(std::stringstream& file, ViewInfo::FramesetInfo& frameset_info)
{
    WrapWriteMessage(file, frameset_info.sprite_name_);
    file << " ";
    WrapWriteMessage(file, frameset_info.state_);
    file << " ";
    file << frameset_info.angle_;
    file << " ";
    return file;
}
std::istream& operator>>(std::stringstream& file, ViewInfo::FramesetInfo& frameset_info)
{
    WrapReadMessage(file, frameset_info.sprite_name_);
    WrapReadMessage(file, frameset_info.state_);
    file >> frameset_info.angle_;
    return file;
}

bool ViewInfo::FramesetInfo::IsSameSprites(
    const ViewInfo::FramesetInfo &left,
    const ViewInfo::FramesetInfo &right)
{
    if (left.sprite_name_ != right.sprite_name_)
    {
        return false;
    }
    if (left.state_ != right.state_)
    {
        return false;
    }
    if (left.angle_ != right.angle_)
    {
        return false;
    }
    return true;
}

ViewInfo::FramesetInfo::FramesetInfo()
{
    sprite_name_ = "";
    state_ = "";
    angle_ = 0;
}

void ViewInfo::FramesetInfo::SetAngle(int angle)
{
    angle_ = angle;
}

void ViewInfo::FramesetInfo::SetSprite(const std::string& name)
{
    sprite_name_ = name;
}

void ViewInfo::FramesetInfo::SetState(const std::string& name)
{
    state_ = name;
}

bool ViewInfo::IsSameFramesets(const ViewInfo &left, const ViewInfo &right)
{
    if (left.underlays_.size() != right.underlays_.size())
    {
        return false;
    }
    if (left.overlays_.size() != right.overlays_.size())
    {
        return false;
    }

    if (left.angle_ != right.angle_)
    {
        return false;
    }

    if (!FramesetInfo::IsSameSprites(left.base_frameset_, right.base_frameset_))
    {
        return false;
    }

    for (int i = 0; i < static_cast<int>(left.underlays_.size()); ++i)
    {
        if (!FramesetInfo::IsSameSprites(left.underlays_[i], right.underlays_[i]))
        {
            return false;
        }
    }
    for (int i = 0; i < static_cast<int>(left.overlays_.size()); ++i)
    {
        if (!FramesetInfo::IsSameSprites(left.overlays_[i], right.overlays_[i]))
        {
            return false;
        }
    }
    return true;
}

ViewInfo::ViewInfo()
{
    angle_ = 0;
}

void ViewInfo::SetAngle(int angle)
{
    angle_ = angle;
}

void ViewInfo::AddOverlay(const std::string& sprite, const std::string& state)
{
    FramesetInfo f;
    f.SetSprite(sprite);
    f.SetState(state);
    overlays_.push_back(f);
}
void ViewInfo::AddUnderlay(const std::string& sprite, const std::string& state)
{
    FramesetInfo f;
    f.SetSprite(sprite);
    f.SetState(state);
    underlays_.push_back(f);
}

void ViewInfo::RemoveOverlays()
{
    overlays_.clear();
}
void ViewInfo::RemoveUnderlays()
{
    underlays_.clear();
}
