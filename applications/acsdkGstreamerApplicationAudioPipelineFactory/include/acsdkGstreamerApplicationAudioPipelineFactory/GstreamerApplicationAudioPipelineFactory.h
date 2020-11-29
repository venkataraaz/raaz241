/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ACSDKGSTREAMERAPPLICATIONAUDIOPIPELINEFACTORY_GSTREAMERAPPLICATIONAUDIOPIPELINEFACTORY_H_
#define ACSDKGSTREAMERAPPLICATIONAUDIOPIPELINEFACTORY_GSTREAMERAPPLICATIONAUDIOPIPELINEFACTORY_H_

#include <memory>
#include <string>

#include <acsdkApplicationAudioPipelineFactoryInterfaces/ApplicationAudioPipelineFactoryInterface.h>
#include <acsdkEqualizerInterfaces/EqualizerRuntimeSetupInterface.h>
#include <acsdkShutdownManagerInterfaces/ShutdownNotifierInterface.h>
#include <AVSCommon/SDKInterfaces/ApplicationMediaInterfaces.h>
#include <AVSCommon/SDKInterfaces/ChannelVolumeFactoryInterface.h>
#include <AVSCommon/SDKInterfaces/HTTPContentFetcherInterfaceFactoryInterface.h>
#include <AVSCommon/SDKInterfaces/SpeakerInterface.h>
#include <AVSCommon/SDKInterfaces/SpeakerManagerInterface.h>
#include <AVSCommon/Utils/MediaPlayer/MediaPlayerInterface.h>
#include <Captions/CaptionManagerInterface.h>

namespace alexaClientSDK {
namespace acsdkGstreamerApplicationAudioPipelineFactory {

/**
 * Factory to create media players and related interfaces for Gstreamer.
 */
class GstreamerApplicationAudioPipelineFactory
        : public acsdkApplicationAudioPipelineFactoryInterfaces::ApplicationAudioPipelineFactoryInterface {
public:
    /**
     * Creates a new instance of @c ApplicationAudioPipelineFactoryInterface.
     *
     * @param channelVolumeFactory The @c ChannelVolumeFactoryInterface to use for creating channel volume interfaces.
     * @param speakerManagerInterface The @c SpeakerManagerInterface with which to register speakers.
     * @param equalizerRuntimeSetup The @c EqualizerRuntimeSetupInterface with which to register equalizers.
     * @param httpContentFetcherFactory The @c HTTPContentFetcherInterfaceFactoryInterface to fetch remote http content.
     * @param shutdownNotifier The @c ShutdownNotifierInterface to notify created media players of shutdown.
     * @param captionManager The @c CaptionManagerInterface to add captionable media sources.
     * @return A new @c ApplicationAudioPipelineFactoryInterface for Gstreamer media players.
     */
    static std::shared_ptr<acsdkApplicationAudioPipelineFactoryInterfaces::ApplicationAudioPipelineFactoryInterface>
    create(
        const std::shared_ptr<avsCommon::sdkInterfaces::ChannelVolumeFactoryInterface>& channelVolumeFactory,
        const std::shared_ptr<avsCommon::sdkInterfaces::SpeakerManagerInterface>& speakerManager,
        const std::shared_ptr<acsdkEqualizerInterfaces::EqualizerRuntimeSetupInterface>& equalizerRuntimeSetup,
        const std::shared_ptr<avsCommon::sdkInterfaces::HTTPContentFetcherInterfaceFactoryInterface>&
            httpContentFetcherFactory,
        const std::shared_ptr<acsdkShutdownManagerInterfaces::ShutdownNotifierInterface>& shutdownNotifier,
        const std::shared_ptr<captions::CaptionManagerInterface>& captionManager);

    /// @name ApplicationAudioPipelineFactoryInterface
    /// @{
    std::shared_ptr<avsCommon::sdkInterfaces::ApplicationMediaInterfaces> createApplicationMediaInterfaces(
        const std::string& name,
        bool equalizerAvailable,
        bool enableLiveMode,
        bool isCaptionable,
        avsCommon::sdkInterfaces::ChannelVolumeInterface::Type channelVolumeType,
        std::function<int8_t(int8_t)> volumeCurve) override;
    std::shared_ptr<acsdkApplicationAudioPipelineFactoryInterfaces::PooledApplicationMediaInterfaces>
    createPooledApplicationMediaInterfaces(
        const std::string& name,
        int numMediaPlayers,
        bool equalizerAvailable,
        bool enableLiveMode,
        bool isCaptionable,
        avsCommon::sdkInterfaces::ChannelVolumeInterface::Type channelVolumeType,
        std::function<int8_t(int8_t)> volumeCurve) override;
    /// @}

private:
    /**
     * Constructor.
     *
     * @param channelVolumeFactory The @c ChannelVolumeFactoryInterface to use for creating channel volume interfaces.
     * @param speakerManagerInterface The @c SpeakerManagerInterface with which to register speakers.
     * @param equalizerRuntimeSetup The @c EqualizerRuntimeSetupInterface with which to register equalizers.
     * @param httpContentFetcherFactory The @c HTTPContentFetcherInterfaceFactoryInterface to fetch remote http content.
     * @param shutdownNotifier The @c ShutdownNotifierInterface to notify created media players of shutdown.
     *  @param captionManager The @c CaptionManagerInterface to add captionable media sources.
     */
    GstreamerApplicationAudioPipelineFactory(
        const std::shared_ptr<avsCommon::sdkInterfaces::ChannelVolumeFactoryInterface>& channelVolumeFactory,
        const std::shared_ptr<avsCommon::sdkInterfaces::SpeakerManagerInterface>& speakerManager,
        const std::shared_ptr<acsdkEqualizerInterfaces::EqualizerRuntimeSetupInterface>& equalizerRuntimeSetup,
        const std::shared_ptr<avsCommon::sdkInterfaces::HTTPContentFetcherInterfaceFactoryInterface>&
            httpContentFetcherFactory,
        const std::shared_ptr<acsdkShutdownManagerInterfaces::ShutdownNotifierInterface>& shutdownNotifier,
        const std::shared_ptr<captions::CaptionManagerInterface>& captionManager);

    /// The @c SpeakerManagerInterface with which to register speakers.
    std::shared_ptr<avsCommon::sdkInterfaces::SpeakerManagerInterface> m_speakerManager;

    /// The @c ChannelVolumeFactoryInterface to use for creating channel volume interfaces.
    std::shared_ptr<avsCommon::sdkInterfaces::ChannelVolumeFactoryInterface> m_channelVolumeFactory;

    /// The @c HTTPContentFetcherInterfaceFactoryInterface to use when creating a media player.
    std::shared_ptr<avsCommon::sdkInterfaces::HTTPContentFetcherInterfaceFactoryInterface> m_httpContentFetcherFactory;

    /// The @c ShutdownNotifierInterface to notify media players of shutdown.
    std::shared_ptr<acsdkShutdownManagerInterfaces::ShutdownNotifierInterface> m_shutdownNotifier;

    /// The @c EqualizerRuntimeSetupInterface with which to register equalizers.
    std::shared_ptr<acsdkEqualizerInterfaces::EqualizerRuntimeSetupInterface> m_equalizerRuntimeSetup;

    /// The @c CaptionManagerInterface with which to register captionable media sources.
    std::shared_ptr<captions::CaptionManagerInterface> m_captionManager;
};

}  // namespace acsdkGstreamerApplicationAudioPipelineFactory
}  // namespace alexaClientSDK

namespace alexaClientSDK {

/**
 * Factory method to create a new instance of @c ApplicationAudioPipelineFactoryInterface.
 *
 * @param channelVolumeFactory The @c ChannelVolumeFactoryInterface to use for creating channel volume interfaces.
 * @param speakerManagerInterface The @c SpeakerManagerInterface with which to register speakers.
 * @param equalizerRuntimeSetup The @c EqualizerRuntimeSetupInterface with which to register equalizers.
 * @param httpContentFetcherFactory The @c HTTPContentFetcherInterfaceFactoryInterface to fetch remote http content.
 * @param shutdownNotifier The @c ShutdownNotifierInterface to notify created media players of shutdown.
 * @param captionManager The @c CaptionManagerInterface to add captionable media sources.
 * @return A new @c ApplicationAudioPipelineFactoryInterface for Gstreamer media players.
 */
inline std::shared_ptr<acsdkApplicationAudioPipelineFactoryInterfaces::ApplicationAudioPipelineFactoryInterface>
createApplicationAudioPipelineFactoryInterface(
    const std::shared_ptr<avsCommon::sdkInterfaces::ChannelVolumeFactoryInterface>& channelVolumeFactory,
    const std::shared_ptr<avsCommon::sdkInterfaces::SpeakerManagerInterface>& speakerManager,
    const std::shared_ptr<acsdkEqualizerInterfaces::EqualizerRuntimeSetupInterface>& equalizerRuntimeSetup,
    const std::shared_ptr<avsCommon::sdkInterfaces::HTTPContentFetcherInterfaceFactoryInterface>&
        httpContentFetcherFactory,
    const std::shared_ptr<acsdkShutdownManagerInterfaces::ShutdownNotifierInterface>& shutdownNotifier,
    const std::shared_ptr<captions::CaptionManagerInterface>& captionManager) {
    return acsdkGstreamerApplicationAudioPipelineFactory::GstreamerApplicationAudioPipelineFactory::create(
        channelVolumeFactory,
        speakerManager,
        equalizerRuntimeSetup,
        httpContentFetcherFactory,
        shutdownNotifier,
        captionManager);
}

}  // namespace alexaClientSDK

#endif  // ACSDKGSTREAMERAPPLICATIONAUDIOPIPELINEFACTORY_GSTREAMERAPPLICATIONAUDIOPIPELINEFACTORY_H_
