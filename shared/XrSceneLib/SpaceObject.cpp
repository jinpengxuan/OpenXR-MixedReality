//*********************************************************
//    Copyright (c) Microsoft. All rights reserved.
//
//    Apache 2.0 License
//
//    You may obtain a copy of the License at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
//    implied. See the License for the specific language governing
//    permissions and limitations under the License.
//
//*********************************************************
#include "pch.h"
#include "SpaceObject.h"

SpaceObject::SpaceObject(SceneContext& sceneContext, std::unique_ptr<xr::SpaceHandle> space, bool hideWhenPoseInvalid)
    : m_sceneContext(sceneContext)
    , m_space(std::move(space))
    , m_hideWhenPoseInvalid(hideWhenPoseInvalid) {
    assert(m_space != nullptr);
}

void SpaceObject::Update(const FrameTime& frameTime) {
    XrSpaceLocation location{XR_TYPE_SPACE_LOCATION};
    xrLocateSpace(m_space->Get(), m_sceneContext.SceneSpace, frameTime.PredictedDisplayTime, &location);
    const bool poseValid = xr::math::Pose::IsPoseValid(location);
    if (poseValid) {
        Pose() = location.pose;
    }
    if (m_hideWhenPoseInvalid) {
        SetVisible(poseValid);
    }
}
