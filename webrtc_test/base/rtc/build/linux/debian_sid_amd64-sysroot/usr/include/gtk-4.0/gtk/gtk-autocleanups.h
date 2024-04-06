/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined (__GTK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gtk/gtk.h> can be included directly."
#endif

#ifndef __GI_SCANNER__

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAccessible, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkActionBar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkActionable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAdjustment, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAppChooser, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAppChooserButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAppChooserDialog, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAppChooserWidget, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkApplicationWindow, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAspectFrame, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkAssistant, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkBox, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkBuildable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkBuilder, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCalendar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellArea, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellAreaBox, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellAreaContext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellEditable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellLayout, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRenderer, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererAccel, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererCombo, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererPixbuf, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererProgress, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererSpin, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererSpinner, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererText, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellRendererToggle, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCellView, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCheckButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCheckMenuItem, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkClipboard, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkColorButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkColorChooser, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkColorChooserDialog, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkColorChooserWidget, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkComboBox, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkComboBoxText, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkCssProvider, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkDrawingArea, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkEditable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkEntry, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkEntryBuffer, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkEntryCompletion, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkEventController, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkExpander, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFileChooserButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFileChooserDialog, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFileChooserWidget, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFileFilter, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFixed, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFlowBox, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFlowBoxChild, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFontButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFontChooser, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFontChooserDialog, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFontChooserWidget, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkFrame, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGLArea, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGesture, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGestureDrag, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGestureLongPress, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGestureMultiPress, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGesturePan, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGestureRotate, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGestureSingle, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGestureSwipe, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGestureZoom, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkGrid, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkHeaderBar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkIMContext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkIMContextSimple, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkIMMulticontext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkIconInfo, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkIconTheme, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkIconView, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkImage, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkInfoBar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkLevelBar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkLinkButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkListStore, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkLockButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkMenuBar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkMenuButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkMenuItem, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkMenuToolButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkMessageDialog, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkMountOperation, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkNotebook, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkOrientable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkOverlay, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPageSetup, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPaned, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPopover, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPopoverMenu, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPrintContext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPrintOperation, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPrintOperationPreview, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPrintSettings, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkProgressBar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkRadioButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkRadioMenuItem, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkRadioToolButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkRange, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkRecentManager, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkRevealer, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkScale, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkScaleButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkScrollable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkScrollbar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkScrolledWindow, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSearchBar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSearchEntry, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSeparator, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSeparatorMenuItem, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSeparatorToolItem, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSettings, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkStackSidebar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSizeGroup, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSpinButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSpinner, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkStack, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkStackSwitcher, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkStatusbar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkStyleContext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkStyleProvider, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSwitch, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTextBuffer, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTextChildAnchor, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTextMark, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTextTag, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTextTagTable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTextView, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkToggleButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkToggleToolButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkToolButton, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkToolItem, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkToolShell, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkToolbar, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTooltip, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeDragDest, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeDragSource, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeModel, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeModelFilter, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeModelSort, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeSelection, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeSortable, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeStore, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeView, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeViewColumn, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkViewport, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkVolumeButton, g_object_unref)

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkPaperSize, gtk_paper_size_free)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkRecentInfo, gtk_recent_info_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkSelectionData, gtk_selection_data_free)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTextIter, gtk_text_iter_free)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeIter, gtk_tree_iter_free)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreePath, gtk_tree_path_free)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkTreeRowReference, gtk_tree_row_reference_free)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GtkWidgetPath, gtk_widget_path_unref)

#endif
