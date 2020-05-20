/**
 * Class QGit::Reference::Detail
 * Widget of a detailed git reference.
 *
 * Tianyun Zhang, 2020, all rights reserved.
 */

#include "reference/detail.h"
using namespace QGit::Reference;

Detail::Detail(bool debug, const QString &hash, QWidget *parent) : QWidget(parent), debug(debug), hash(hash) {}
