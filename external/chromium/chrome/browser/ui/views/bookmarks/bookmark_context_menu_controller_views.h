// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_BOOKMARKS_BOOKMARK_CONTEXT_MENU_CONTROLLER_VIEWS_H_
#define CHROME_BROWSER_UI_VIEWS_BOOKMARKS_BOOKMARK_CONTEXT_MENU_CONTROLLER_VIEWS_H_

#include <vector>

#include "base/basictypes.h"
#include "chrome/browser/bookmarks/base_bookmark_model_observer.h"

class Browser;
class Profile;

namespace content {
class PageNavigator;
}

namespace views {
class Widget;
}

// An interface implemented by an object that performs actions on the actual
// menu for the controller.
class BookmarkContextMenuControllerViewsDelegate {
 public:
  virtual ~BookmarkContextMenuControllerViewsDelegate() {}

  // Closes the bookmark context menu.
  virtual void CloseMenu() = 0;

  // Methods that add items to the underlying menu.
  virtual void AddItemWithStringId(int command_id, int string_id) = 0;
  virtual void AddSeparator() = 0;
  virtual void AddCheckboxItem(int command_id, int string_id) = 0;

  // Sent before bookmarks are removed.
  virtual void WillRemoveBookmarks(
      const std::vector<const BookmarkNode*>& bookmarks) {}

  // Sent after bookmarks have been removed.
  virtual void DidRemoveBookmarks() {}
};

// BookmarkContextMenuControllerViews creates and manages state for the context
// menu shown for any bookmark item.
class BookmarkContextMenuControllerViews : public BaseBookmarkModelObserver {
 public:
  // Factory function for creating an instance of the
  // BookmarkContextMenuControllerViews class which in turn creates the
  // bookmark context menu.
  // |parent_widget| is the window that this menu should be added to.
  // |delegate| is described above.
  // |browser| is used to open the bookmark manager and is NULL in tests.
  // |profile| is used for opening urls as well as enabling 'open incognito'.
  // |navigator| is used if |browser| is null, and is provided for testing.
  // |parent| is the parent for newly created nodes if |selection| is empty.
  // |selection| is the nodes the context menu operates on and may be empty.
  static BookmarkContextMenuControllerViews* Create(
      views::Widget* parent_widget,
      BookmarkContextMenuControllerViewsDelegate* delegate,
      Browser* browser,
      Profile* profile,
      content::PageNavigator* navigator,
      const BookmarkNode* parent,
      const std::vector<const BookmarkNode*>& selection);

  virtual ~BookmarkContextMenuControllerViews();

  virtual void ExecuteCommand(int id);
  virtual bool IsItemChecked(int id) const;
  virtual bool IsCommandEnabled(int id) const;

  void BuildMenu();

  void set_navigator(content::PageNavigator* navigator) {
    navigator_ = navigator;
  }

 protected:
  // Creates the bookmark context menu.
  // |parent_widget| is the window that this menu should be added to.
  // |delegate| is described above.
   // |browser| is used to open the bookmark manager and is NULL in tests.
  // |profile| is used for opening urls as well as enabling 'open incognito'.
  // |navigator| is used if |browser| is null, and is provided for testing.
  // |parent| is the parent for newly created nodes if |selection| is empty.
  // |selection| is the nodes the context menu operates on and may be empty.
  BookmarkContextMenuControllerViews(
      views::Widget* parent_widget,
      BookmarkContextMenuControllerViewsDelegate* delegate,
      Browser* browser,
      Profile* profile,
      content::PageNavigator* navigator,
      const BookmarkNode* parent,
      const std::vector<const BookmarkNode*>& selection);

  const Profile* profile() const { return profile_; }
  Profile* profile() { return profile_; }

  views::Widget* parent_widget() { return parent_widget_; }

  const std::vector<const BookmarkNode*>& selection() const {
    return selection_;
  }

 private:
  // Overridden from BaseBookmarkModelObserver:
  // Any change to the model results in closing the menu.
  virtual void BookmarkModelChanged() OVERRIDE;

  // Removes the observer from the model and NULLs out model_.
  BookmarkModel* RemoveModelObserver();

  views::Widget* parent_widget_;
  BookmarkContextMenuControllerViewsDelegate* delegate_;
  Browser* browser_;
  Profile* profile_;
  content::PageNavigator* navigator_;
  const BookmarkNode* parent_;
  std::vector<const BookmarkNode*> selection_;
  BookmarkModel* model_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkContextMenuControllerViews);
};

#endif  // CHROME_BROWSER_UI_VIEWS_BOOKMARKS_BOOKMARK_CONTEXT_MENU_CONTROLLER_VIEWS_H_
