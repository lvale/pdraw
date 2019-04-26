/**
 * Parrot Drones Awesome Video Viewer Library
 * Renderer interface
 *
 * Copyright (c) 2018 Parrot Drones SAS
 * Copyright (c) 2016 Aurelien Barre
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the copyright holders nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _PDRAW_RENDERER_HPP_
#define _PDRAW_RENDERER_HPP_

#include "pdraw_element.hpp"
#include "pdraw_sink.hpp"

#include <pdraw/pdraw.hpp>

namespace Pdraw {

class Renderer : public Element, public Sink {
public:
	virtual ~Renderer(void);

	virtual int setup(const struct pdraw_rect *renderPos,
			  const struct pdraw_video_renderer_params *params,
			  struct egl_display *eglDisplay) = 0;

	virtual int render(struct pdraw_rect *contentPos,
			   const float *viewMat = NULL,
			   const float *projMat = NULL) = 0;

	virtual int resize(const struct pdraw_rect *renderPos) = 0;

	virtual int
	setParams(const struct pdraw_video_renderer_params *params) = 0;

	virtual int getParams(struct pdraw_video_renderer_params *params) = 0;

	virtual void completeStop(void) = 0;

	static Renderer *create(Session *session,
				Element::Listener *listener,
				IPdraw::VideoRendererListener *rndListener);

protected:
	Renderer(Session *session,
		 Element::Listener *listener,
		 IPdraw::VideoRendererListener *rndListener,
		 uint32_t mediaTypeCaps,
		 uint32_t videoMediaFormatCaps,
		 uint32_t videoMediaSubFormatCaps);

	void removeRendererListener(void);

	IPdraw::VideoRendererListener *mRendererListener;
	pthread_mutex_t mListenerMutex;
};

} /* namespace Pdraw */

#endif /* !_PDRAW_RENDERER_HPP_ */
