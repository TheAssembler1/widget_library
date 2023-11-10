#pragma once

#include "../attr/transform.h"
#include "../base_widget.h"

namespace Widget {

class HContainer : public BaseWidget {
	public:
		HContainer() : BaseWidget(Transform(0, 0, 0, 0)) {}
		void toStringPrint() const override;
};

}