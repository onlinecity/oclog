/*
 * Copyright (C) 2011 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 * @author hd@onlinecity.dk & td@onlinecity.dk
 */

#ifndef OCMACROS_H_
#define OCMACROS_H_

#include "Log.h"

#ifndef OC_LOG_MAX_LEVEL
#define OC_LOG_MAX_LEVEL oc::log::DEBUG
#endif

#define OC_LOG(sinktype,category,level) \
    if (level > OC_LOG_MAX_LEVEL) ;\
    else if (level > oc::log::Log<sinktype>::getLevel()) ; \
    else oc::log::Log<sinktype>(category).get()

#endif /* OCMACROS_H_ */
